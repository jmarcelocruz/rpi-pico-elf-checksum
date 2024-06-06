# Copyright 2024 José Marcelo Marques da Cruz
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

CXXFLAGS = -std=c++11 -Iinclude/ ${EXTRA_CXXFLAGS}
LDFLAGS = ${EXTRA_LDFLAGS}

SOURCES =
OBJS = $(patsubst %.cpp,%.o,${SOURCES})

rpi-pico-elf-checksum.elf: ${OBJS}
	${CXX} $^ ${LDFLAGS} -o $@

${OBJS}: %.o: %.cpp
	${CXX} -c $^ ${CXXFLAGS} -o $@

.PHONY: clean
clean:
	rm -f rpi-pico-elf-checksum.elf ${OBJS}
