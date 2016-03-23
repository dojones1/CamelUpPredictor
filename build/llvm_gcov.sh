#!/bin/sh

#  llvm_gcov.sh
#  camelUpPredictor
#
#  Created by Donald Jones on 23/03/2016.
#  Copyright © 2016 Donald Jones. All rights reserved.
exec llvm-cov gcov "$@"