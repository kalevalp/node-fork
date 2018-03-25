const {fork, wait, read, write, pipe} = require('./build/Release/fork');

module.exports.fork = function() {
    pid = fork();
    
    return pid == 0;
}

module.exports.wait = function() {
    wait();
}

const pipes = pipe();

if (fork()) { // parent
    console.log("In parent");
    message = read(pipes.read_end);
    console.log("Waiting");
    wait();
    console.log("Waited");
    console.log(message);
} else { // child
    console.log("In child");
    // setTimeout(function() {
        write(pipes.write_end, "Hello from child");
        console.log("Sent");      
    // }, 3000);
}



