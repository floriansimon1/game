#!/bin/bash

scriptDirectory="$(cd "$(dirname "${BASH_SOURCE[0]}")" > /dev/null 2>&1 && pwd)"

rm -r "${scriptDirectory}/../generated"

mkdir -p "${scriptDirectory}/../generated"

export CONAN_SYSREQUIRES_MODE=enabled
cmake "${scriptDirectory}/.." -B "${scriptDirectory}/../generated"
