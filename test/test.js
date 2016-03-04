/**
 * XadillaX created at 2016-03-03 18:13:42 With ♥
 *
 * Copyright (c) 2016 Souche.com, all rights
 * reserved.
 */
"use strict";

var syncRunner = require("sync-runner");

describe(function() {
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
            syncRunner("useradd -m test");
            var result = syncRunner("sudo -u test node test/test_script.js");
            result.should.be.eql("/home/test");
        }
    });
});