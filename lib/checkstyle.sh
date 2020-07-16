#!/bin/bash -e

scriptdir=$(dirname "$0")

if [ "$1" == "" ]; then
    diffoutput="./formatdiff.txt"
else
    diffoutput="$1"
fi
: > "$diffoutput"

running_on_server=false
[ -n "$GITLAB_CI" ] && running_on_server=true

cd $scriptdir/..

# Check whether clang-format is available
hash clang-format-9 2>/dev/null || { echo >&2 "Required tool clang-format-9 not found. Aborting."; exit 1; }

# We want to scan all files that were changed since master branch-off,
# that's what "git merge-base" finds.

if $running_on_server ; then
    # Gitlab has no valid HEAD, since it checks out one specific commit
    # from the entire current repo.
    # Also, does minimal checkout that doesn't have "master" immediately
    # available; we need to fetch explicitly.
    # Some details: https://gitlab.com/gitlab-org/gitlab-runner/issues/4557

    THISCOMMIT="$CI_COMMIT_SHA"
    git fetch origin
    git fetch origin master:master

    # "git merge-base X master" returns X if X is on master.
    # We always have a full commit, and want to check from the closest
    # *parent* that is on master. So start searching from parent X^.
    # This is also valid when working on master. (No, you shouldn't do that.)
    # On merge commit, "leftmost parent" $THISCOMMIT^ will be previous master,
    # which is also precisely what we want.

    PREVCOMMIT="`git merge-base "$THISCOMMIT"^ master`"
    echo "Comparing changed files from $PREVCOMMIT to $THISCOMMIT"
    files_to_check="`git diff "$PREVCOMMIT" "$THISCOMMIT" --name-only`"

else
    # Locally there may be changes pending since HEAD;
    # also HEAD may be master when we are preparing to branch off.
    # Accept HEAD as reference *if* that produces any changed files;
    # otherwise seek back from HEAD^.

    PREVCOMMIT="`git merge-base HEAD master`"
    files_to_check="`git diff "$PREVCOMMIT" --name-only`"
    if [ -z "$files_to_check" ] ; then
        PREVCOMMIT="`git merge-base HEAD^ master`"
        files_to_check="`git diff "$PREVCOMMIT" --name-only`"
    fi
    echo "Comparing changed files from $PREVCOMMIT to current"
fi

needToCheckFile()
{
    # We only need to check C++ header and source files
    if [[ $1 == *.cpp ]];then
        return 0
    elif [[ $1 == *.h ]];then
        return 0
    fi

    return 1
}

echo "Checking coding style..."

exit_code=0
failures=""
for file in $files_to_check; do
    if [ -f "$file" ]; then 
        if needToCheckFile "$file"; then
            echo "Checking $file" >> "$diffoutput"
            if ! clang-format-9 "$file" | diff -u "$file" - >> "$diffoutput" ; then
                failures+="  - $file"$'\n'
                exit_code=1
            fi
        fi
    fi
done

if [[ $exit_code == 0 ]]; then
    echo "Excellent! No coding style issues detected."
else
    echo "Issues found in the following files:"
    echo "$failures"
    echo "See $diffoutput for details."
    if $running_on_server ; then
        echo "  -> download from gitlab artifacts."
    fi
    echo "Please run clang-format-9 on the indicated files."
    echo ""
fi

exit $exit_code
