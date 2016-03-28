'use strict';

const http = require('http');
const port = 8087;

function handler(req, res) {
  let body = '';

  req.on('data', data => {
    if (data === undefined) {
      return;
    }
    body += data;
  });

  req.on('end', () => {
    console.log(body);
  });

  res.end('message received');
}

http
  .createServer(handler)
  .listen(port, () => {
    console.log("Listening on: http://localhost:%s", port);
});
