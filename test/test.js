/**
 * XadillaX created at 2016-03-03 18:13:42 With ♥
 *
 * Copyright (c) 2016 Souche.com, all rights
 * reserved.
 */
"use strict";

require("should");

describe("homedir", function() {
    var homedir = require("../");

    it("should equal to $HOME and os", function() {
        var hd = homedir();
        hd.should.be.eql(process.env.HOME);

        var os = require("os");
        if(undefined !== os.homedir) {
            hd.should.be.eql(require("os").homedir());
        }
    });

    it("should equal to another user", function() {
        if(process.env.TRAVIS) {
            var syncRunner = require("sync-runner");
            var result = syncRunner("sudo -u test " + process.execPath + " test_script.js", __dirname);
            result.trim().should.be.eql(process.env.HOME + "\n/home/test");
        }
    });

    it("should equal to another user with -i", function() {
        if(process.env.TRAVIS) {
            var syncRunner = require("sync-runner");
            var result = syncRunner("sudo -u test -i " + process.execPath + " " + __dirname + "/test_script.js");
            result.trim().should.be.eql("/home/test\n/home/test");
        }
    });
});
