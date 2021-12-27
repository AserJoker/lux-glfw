# @lux/glfw

A nodejs adapter to use glfw library [@glfw](https://github.com/glfw/glfw)


## Table of Contents

- [@lux/glfw](#luxglfw)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Install](#install)
  - [Usage](#usage)
  - [Example](#example)
  - [Maintainers](#maintainers)
  - [Contributing](#contributing)
    - [Contributors](#contributors)
  - [License](#license)

## Introduction

@lux/glfw is a part of lux.js for transform C-language library glfw to nodejs


## Install

This project uses [node](http://nodejs.org) and [npm](https://npmjs.com). Go check them out if you don't have them locally installed.

```sh
$ npm install --save @lux/glfw
```

## Usage

@lux/glfw support most intefraces for glfw,except userdata* API(
    glfwGetJoystickUserPointer
    glfwGetMonitorUserPointer
    glfwGetWindowUserPointer
    glfwSetJoystickUserPointer
    glfwSetMonitorUserPointer
    glfwSetWindowUserPointer)

all glfw API was added CXX_ as prefix like CXX_glfwInit.
for image @lux/glfw add CXX_createImage & CXX_deleteImage to create/delete a image object.

## Example

this is a simple demo to create a window and set a red rect to replace default cursor;
```typescript
import glfw from "@lux/glfw";
glfw.CXX_glfwInit();
const window = glfw.CXX_glfwCreateWindow(1024, 768, "glfw-node");
const img = new Int32Array(32 * 32);
img.fill(0xff0000ff, 0, 32 * 32);
const image = glfw.CXX_createImage(32, 32, img);
const cursor = glfw.CXX_glfwCreateCursor(image, 0, 0);
glfw.CXX_deleteImage(image);
glfw.CXX_glfwSetCursor(window, cursor);
while (!glfw.CXX_glfwWindowShouldClose(window)) {
  if (
    glfw.CXX_glfwGetKey(window, glfw.KEY.ESCAPE) === glfw.ACTION.PRESS
  ) {
    glfw.CXX_glfwSetWindowShouldClose(window, true);
  }
  glfw.CXX_glfwPollEvents();
}
glfw.CXX_glfwTerminate();

```

## Maintainers

[@AserJoker](https://github.com/AserJoker).

## Contributing

Feel free to dive in! [Open an issue](https://github.com/AserJoker/lux-glfw/issues/new) or submit PRs.

### Contributors



## License

[MIT](LICENSE) © AserJoker