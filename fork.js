const fork = require('./build/Release/fork');


module.exports.fork = function() {
    pid = fork.fork();

    return pid == 0;
}

