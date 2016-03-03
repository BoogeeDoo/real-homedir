/**
 * XadillaX created at 2016-03-03 18:10:05 With ♥
 *
 * Copyright (c) 2016 Souche.com, all rights
 * reserved.
 */
"use strict";

var _homedir = require("./build/Release/homedir");

module.exports = function() {
    return _homedir.homedir();
};
