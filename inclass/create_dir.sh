#!/bin/bash
if [ -d testdir ]; then
     echo -n "Overwrite existing testdir directory? (Y/N): "
     read answer
     if [ ! $answer = "Y" ]; then
         exit 1;
     fi
     rm -rf ./testdir
fi
mkdir testdir
mkdir testdir/dir1
mkdir testdir/dir2
mkdir testdir/dir3
mkdir testdir/dir1/subdir1
mkdir testdir/dir1/subdir2
mkdir testdir/dir1/subdir3
mkdir testdir/dir2/subdir1
mkdir testdir/dir2/subdir2
mkdir testdir/dir3/subdir1
touch testdir/file1
touch testdir/file2
touch testdir/dir1/file3
touch testdir/dir2/file4
touch testdir/dir3/file5
touch testdir/dir1/subdir1/file6
touch testdir/dir1/subdir2/file7
touch testdir/dir1/subdir3/file8
touch testdir/dir2/subdir1/file9
touch testdir/dir2/subdir2/file10
touch testdir/dir3/subdir1/file11
cp /bin/ls testdir/file21
cp /bin/ls testdir/file22
cp /bin/ls testdir/dir1/file23
cp /bin/ls testdir/dir2/file24
cp /bin/ls testdir/dir3/file25
cp /bin/ls testdir/dir1/subdir1/file26
cp /bin/ls testdir/dir1/subdir2/file27
cp /bin/ls testdir/dir1/subdir3/file28
cp /bin/ls testdir/dir2/subdir1/file29
cp /bin/ls testdir/dir2/subdir2/file30
cp /bin/ls testdir/dir3/subdir1/file31
