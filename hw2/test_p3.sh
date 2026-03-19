#!/bin/bash
# Creates a test directory with some files and one duplicate so you can run p3.sh yourself.

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TEST_DIR="${SCRIPT_DIR}/testdir"

rm -rf "$TEST_DIR"
mkdir -p "$TEST_DIR/subdir"

echo "content a"       > "$TEST_DIR/file_a.txt"
echo "content b"       > "$TEST_DIR/file_b.txt"
echo "content a copy"  > "$TEST_DIR/subdir/file_a.txt"
echo "content c"       > "$TEST_DIR/subdir/file_c.txt"

echo "Test directory created: $TEST_DIR"
echo ""
echo "Run your program with:"
echo "  ./p3.sh $TEST_DIR"
echo ""
