# BSD 3-Clause License
#
# Copyright (c) 2025, Dror Smolarsky
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
'''Xykivo percipio Python coroutine example
'''

import asyncio
import time


async def delayed_print(in_text, in_wait_time):
    '''Print text to standard output after a timed delay
    '''
    print(in_text, '- sleep for', in_wait_time, 'seconds')
    await asyncio.sleep(in_wait_time)
    print(in_text, 'complete')


async def main():
    '''Main async entry point
    '''
    print('async main ->')
    print('await delyed print A')
    await delayed_print('delayed text A - in 3 seconds', 3)

    print('await croutine object returned from croutines')
    task_b = delayed_print('delayed text B', 3)
    task_c = delayed_print('delayed text C', 2)
    await task_b
    await task_c

    print('run croutines concurrently')
    await asyncio.gather(delayed_print('delayed text D', 3),
                         delayed_print('delayed text E', 2),
                         delayed_print('delayed text F', 1))

    # print('async main <-')


if '__main__' == __name__:
    print('croutine example')
    asyncio.run(main())
