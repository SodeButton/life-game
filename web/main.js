let world = [];
let old_world = [];
let update;
let time = 500;
let isPlaying = false;

document.getElementById("time-slider").addEventListener("change", () => {
    time = Number(document.getElementById("time-slider").value);
    if (isPlaying) play();
});

document.getElementById("size-option").addEventListener("change", () => {
    changeCanvasSize();
    stop();
});

document.getElementById("canvas").addEventListener("click", e => {
    const rect = e.target.getBoundingClientRect();
    const mouseX = e.clientX - Math.floor(rect.left) - 2;
    const mouseY = e.clientY - Math.floor(rect.top) - 2;

    let cell = cellToPosition(mouseX, mouseY);
    putCell(cell.x, cell.y);
    drawGrid();
    stop();
});

function stop() {
    isPlaying = false;
    clearInterval(update);
}

function step() {
    let width = getWidth();
    let height = getHeight();
    for (let x = 0; x < width; x++) {
        for (let y = 0; y < height; y++) {
            let n = getAdjacentLivesCount(x, y);
            let next = world[x][y];

            if (world[x][y] == 1) {
                if (n <= 1 || n >= 4) {
                    next = 0;
                }
            } else {
                if (n == 3) {
                    next = 1;
                }
            }
            old_world[x][y] = next;
        }
    }
    changeGeneration();
    drawGrid();
}

function play() {
    stop();
    isPlaying = true;
    update = setInterval(() => {
        step();
    }, time);
}

function changeGeneration() {
    let width = getWidth();
    let height = getHeight();
    for (let x = 0; x < width; x++) {
        for (let y = 0; y < height; y++) {
            world[x][y] = old_world[x][y];
        }
    }
}

function getAdjacentLivesCount(_x, _y) {
    let count = 0;
    let width = Number(getWidth());
    let height = Number(getHeight());
    let p = [-1, -1, -1, 0, 0, 1, 1, 1], q = [-1, 0, 1, -1, 1, -1, 0, 1];

    for (let i = 0; i < 8; i++) {
        let x2 = (width + _x + p[i]) % width;
        let y2 = (height + _y + q[i]) % height;
        if (world[x2][y2] == 1) count++;
    }
    
    return count;
}

function changeCanvasSize() {
    const canvas = document.getElementById("canvas");
    const width = getWidth();
    const height = getHeight();
    canvas.width = width * 16;
    canvas.height = height * 16;
    for (let x = 0; x < width; x++) {
        if (world[x] == undefined) world[x] = [];
        old_world[x] = [];
        for (let y = 0; y < height; y++) {
            if (world[x][y] == undefined) world[x][y] = 0;
            old_world[x][y] = 0;
        }
    }
    drawGrid();
}

function getWidth() {
    return document.getElementById("width").value;
}

function getHeight() {
    return document.getElementById("height").value;
}

function drawGrid() {
    const canvas = document.getElementById("canvas");
    if (!canvas.getContext) return;
    const ctx = canvas.getContext("2d");
    for (let x = 0; x < getWidth(); x++) {
        for (let y = 0; y < getHeight(); y++) {
            if (world[x][y] == 0) {
                ctx.clearRect(x * 16, y * 16, 16, 16);
                ctx.strokeRect(x * 16, y * 16, 16, 16);
            } else {
                ctx.clearRect(x * 16, y * 16, 16, 16);
                ctx.fillRect(x * 16 + 1, y * 16 + 1, 16 - 1, 16 - 1);
            }
        }
    }
}

function cellToPosition(mouseX, mouseY) {
    let cell = {x: 0, y: 0};
    let x = Math.floor(mouseX / 16);
    let y = Math.floor(mouseY / 16);

    cell.x = x;
    cell.y = y;

    return cell;
}

function putCell(x, y) {
    world[x][y] ^= 1;
}

window.onload = function() {
    changeCanvasSize();
}