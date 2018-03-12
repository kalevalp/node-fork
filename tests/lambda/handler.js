'use strict';

const { fork, wait }  = require('fork');
const { spawn } = require('child_process');

module.exports.hello = (event, context, callback) => {

    const is_child = fork();
    
    if (is_child) {
        console.log("Hello from Child");
        setTimeout(() => 
            callback(null,
                     { 
                         message: 'Callback from Child!', 
                         event 
                     })
                  , 1000);
    } else {       
        console.log("Hello from Parent");
        wait();
        console.log("Hello again from Parent");
    }

    // const response = {
    //   statusCode: 200,
    //   body: JSON.stringify({
    //     message: 'Go Serverless v1.0! Your function executed successfully!',
    //     input: event,
    //   }),
    // };
    // callback(null, response);


};
