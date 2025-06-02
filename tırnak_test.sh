#!/bin/bash

echo "--- Basic quotes ---"
echo "hello world"
echo 'hello world'

echo "--- Nested quotes ---"
echo "hello 'nested' quotes"
echo 'hello \"nested\" quotes'

echo "--- Escaped quotes ---"
echo "escaped \" quote"

echo "--- Empty quotes ---"
echo ""
echo ''

echo "--- Quotes with spaces ---"
echo "    "
echo '    '

echo "--- Double empty quotes ---"
echo "" ""

echo "--- Mixed adjacent quotes ---"
echo 'foo'"bar"'baz'

echo "--- Single quotes with escape (should not interpret) ---"
echo 'it\'s fine'

echo "--- Backslash inside double quotes ---"
echo "escaped \\ backslash"

echo "--- End of test ---"
