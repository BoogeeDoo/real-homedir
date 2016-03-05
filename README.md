# Real Homedir

[![Real Homedir](http://img.shields.io/npm/v/real-homedir.svg)](https://www.npmjs.org/package/real-homedir)
[![Real Homedir](http://img.shields.io/npm/dm/real-homedir.svg)](https://www.npmjs.org/package/real-homedir)
[![Build Status](https://travis-ci.org/BoogeeDoo/real-homedir.svg?branch=master)](https://travis-ci.org/BoogeeDoo/real-homedir)
[![Coverage Status](https://img.shields.io/coveralls/BoogeeDoo/real-homedir/master.svg)](https://coveralls.io/r/BoogeeDoo/real-homedir?branch=master)
[![License](https://img.shields.io/npm/l/real-homedir.svg?style=flat)](https://www.npmjs.org/package/real-homedir)
[![Dependency Status](https://david-dm.org/BoogeeDoo/real-homedir.svg)](https://david-dm.org/BoogeeDoo/real-homedir)

Get real home directory in node.js.

## Why This Package?

Consider this situation:

You're user **blah**. You run command `$ sudo -u foo node bar.js` and `bar.js` will write some file in executor's (**foo**) home directory.

### $HOME

When you use `process.env.HOME` in `bar.js` with above command, you may won't get `/home/foo` but get `/home/blah`.

### os.homedir()

When you use `os` module shown below:

```javascript
const os = require("os");
console.log(os.homedir());
```

You may won't get `/home/foo` but get `/home/blah` too due to code of [node.js](https://github.com/nodejs/node/blob/v4.3.2/src/node_os.cc#L274-L290) and [libuv](https://github.com/libuv/libuv/blob/v1.8.0/src/unix/core.c#L1032).

### So

You need this package to get the real home directory of current executor due to the situation above, and not only the situation above!

## Installation

```sh
$ npm install -d --save real-homedir
```

## Usage

Require this package first:

```javascript
const homedir = require("real-homedir");
```

And just call it.

```javascript
const hd = homedir();
```

Then you will get the real home directory!

## Contribution

You're welcome to make pull requests!

「雖然我覺得不怎麼可能有人會關注我」
