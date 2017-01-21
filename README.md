# HelloOpenCV

## Requirements

* OpenCV 2.x
* g++

tested on:

* OpenCV 2.7
* g++ 4.2.1

## LICENSE
This software is released under the MIT License, see [LICENSE](./LICENSE).

This project includes the work that is distributed in the 3-clause BSD License.

[opencv/LICENSE](https://github.com/Itseez/opencv/blob/master/LICENSE)

## Troubleshooting
### cascade
`OpenCV Error: Null pointer (Invalid classifier cascade)`

`error: (-27) Invalid classifier cascade`

Check the location of cascade file(s).

e.g.) `haarcascade_frontalface_default.xml`
