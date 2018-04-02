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

if (process.argv[2] === "test") {
    const before_pipes = Date.now();
    const pipes = pipe();

    const before_fork = Date.now();

    if (fork()) { // parent
        console.log("Fork took ", Date.now()-before_fork);
        console.log("Pipe took", before_fork-before_pipes)
        

        close(pipes.write_end);
        
        console.log("In parent");
        message = read(pipes.read_end);
        console.log("After read: ", Date.now());
        console.log("Waiting");
        wait();

        close(pipes.read_end);
        
        console.log("Waited");
        console.log(message);
    } else { // child
        close(pipes.read_end);
        
        console.log("In child");
        console.log("Before write: ", Date.now());

        write(pipes.write_end, "Hello from child");
        console.log("Sent");      

        close(pipes.write_end);
    }



}
