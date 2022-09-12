// i do this cause JavaScript is easy for me and know how work any

const fs = require('fs');

const file = fs.openSync("basic_test.bmp", 'r');

var info = Buffer.alloc(54);

fs.readSync(file, info, 0, 54, 0);


for(var i = 0; i < 54; i++) {
    console.log(`${i} - ${info[i]}`);
}

console.log(`I know at byte "18" in array has the width: ${info[18]}`);
console.log(`And at byte "22" has height: ${info[22]}`);
