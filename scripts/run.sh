#!/bin/bash

scriptDirectory="$(cd "$(dirname "${BASH_SOURCE[0]}")" > /dev/null 2>&1 && pwd)"

cd "${scriptDirectory}/../generated/output"

./game || true

cd -
