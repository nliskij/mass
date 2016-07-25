OUTPUT=$(TCMALLOC_LARGE_ALLOC_REPORT_THRESHOLD=10 tests/test_tcmalloc_binary 2>&1)

if [[ -z "${OUTPUT}" ]]; then
  echo 'Expected output but there was none!' >&2
  exit 1
fi

PATTERN='tcmalloc: large alloc [0-9]+ bytes =='

if [[ ! "${OUTPUT}" =~ ${PATTERN} ]]; then
  echo 'Unexpected output:' >&2
  echo "${OUTPUT}" >&2
  exit 1
fi
