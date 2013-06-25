// tscript_server.js
var http = require("http");
var express = require("express");
var url = require("url");
var server = express();

server.get("/comm", function(req, res) {
    console.log('connection to 8001');
    res.end("hello, world!");
});

server.listen(8001);