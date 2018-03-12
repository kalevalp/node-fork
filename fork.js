const {fork, wait} = require('./build/Release/fork');

module.exports.fork = function() {
    pid = fork();
    
    return pid == 0;
}

module.exports.wait = function() {
    wait();
}

