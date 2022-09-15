const { execSync } = require('child_process');
const path = require('path');
const fs = require('fs');
const os = require('os');

if(fs.existsSync("build")) {
    fs.rmSync("build", { recursive: true });
}

fs.mkdirSync("build");

var hasGcc = false;

try {
    var stdout = execSync(`${process.platform == 'win32' ? 'where' : 'whereis'} g++`, {stdio:[]});
    hasGcc = !!stdout;
} catch {}

process.stdout.write(
    execSync(`cd "${path.join(__dirname, "build")}" && cmake ${hasGcc && process.platform == 'win32' ? '-G "MinGW Makefiles" ' : ''}.. && cmake --build . -j ${os.cpus().length}`)
);

var resultName = "image-to-image-of-characters";

if(process.platform == 'win32') {
    resultName = resultName + ".exe";
}

fs.copyFileSync(path.join(__dirname, "build", resultName), path.join(__dirname, resultName));