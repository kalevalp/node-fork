const {fork, wait} = require('fork')

const is_child = fork();

if (is_child) {
    console.log("Child");
    setTimeout(() => console.log("Still child!"), 3000);
} else {
    wait();
    console.log("Parent done");
}
