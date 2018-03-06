const fork = require('./build/Release/fork');


module.export.fork = function() {
    pid = fork.fork();

    return fork == 0;
}

