var http = require('http');  
var url = require('url');  
var fs = require('fs'); 

var server = http.createServer(function(request, response) {  
  var path = url.parse(request.url).pathname;  
  switch (path) {  
      case '/':  
          response.writeHead(200, {  
              'Content-Type': 'text/plain'  
          });  
          response.write("");  
          response.end();  
          break;  
      case '/data.txt':  
          fs.readFile('command.txt', function(error, data) {  
              if (error) {  
                  response.writeHead(404);  
                  response.write(error);  
                  response.end();  
              } else {  
                  response.writeHead(200, {  
                      'Content-Type': 'text/html'  
                  });  
                  response.write(data);  
                  response.end();  
              }  
          });  
          break;    
        case '/ink32.ink':  
          fs.readFile('ink32.ink', function(error, data) {  
              if (error) {  
                  response.writeHead(404);  
                  response.write(error);  
                  response.end();  
              } else {  
                  response.writeHead(200, {  
                      'Content-Type': 'text/html'  
                  });  
                  response.write(data);  
                  response.end();  
              }  
          });  
          break;
          case '/hash.txt':  
          fs.readFile('hash.txt', function(error, data) {  
              if (error) {  
                  response.writeHead(404);  
                  response.write(error);  
                  response.end();  
              } else {  
                  response.writeHead(200, {  
                      'Content-Type': 'text/html'  
                  });  
                  response.write(data);  
                  response.end();  
              }  
          });  
          break;
      default:  
          response.writeHead(404);  
          response.write("get out from here...");  
          response.end();  
          break;  
  }  
});  
server.listen(8080,'0.0.0.0');  