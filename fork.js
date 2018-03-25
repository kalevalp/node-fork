const {fork, wait, read, write, pipe, close} = require('./build/Release/fork');

module.exports.fork = function() {
    pid = fork();
    
    return pid == 0;
}

module.exports.wait = wait;
module.exports.read = read;
module.exports.write = write;
module.exports.pipe = pipe;
module.exports.close = close;

// const pipes = pipe();

// if (fork()) { // parent
    
//     close(pipes.write_end);
    
//     console.log("In parent");
//     message = read(pipes.read_end);
//     console.log("Waiting");
//     wait();

//     close(pipes.read_end);
    
//     console.log("Waited");
//     console.log(message);
// } else { // child
//     close(pipes.read_end);
    
//     console.log("In child");
//     write(pipes.write_end, "Hello from child");
//     console.log("Sent");      

//     close(pipes.write_end);
// }



