function clamp(val, min, max) {
    if (val < min) {
        return min;
    }
    if (val > max) {
        return max;
    }
    return val;
}

function rig(val) {
    if (val == 0) {
        return val + Math.random() / 100
    }
    return val
}

function randVel() {
    return [(Math.ceil(Math.random() * 8) - 4) / 2,
    (Math.ceil((Math.random() * 8) - 4)) / 2]
}

class sqr {
    constructor(canvas) {
        this.canv = canvas;
        this.vel = randVel();
        while (!(this.vel[0] != 0 && this.vel[1] != 0)) {
            this.vel = randVel();
        }
        this._size = 25
        this._position = [clamp(Math.ceil(Math.random() * (canvas.width - this.size)), 0, canvas.width - this.size),
        clamp(Math.ceil(Math.random() * (canvas.height - this.size)), 0, canvas.height - this.size)]
        this.type = Math.floor(Math.random() * 3) // 0 is rock; 1 is paper; 2 is scissors;
        return this;
    };

    get position() {
        return this._position;
    }

    get size() {
        return this._size;
    }

    update() {
        this._position = [this._position[0] + this.vel[0], this._position[1] + this.vel[1]];
        if (this._position[0] < 0 || this._position[0] > this.canv.width - this.size) {
            this.vel[0] *= -1;
        }
        if (this._position[1] < 0 || this._position[1] > this.canv.height - this.size) {
            this.vel[1] *= -1;
        }
        for (let i = 0; i < sqrs.length; i++) {
            const other = sqrs[i];
            const r = this.collision(other)
            if (r == true) {
                if (other.type === 0 && this.type === 2) {
                    this.type = 0;
                }
                if (other.type === 1 && this.type === 0) {
                    this.type = 1;
                }
                if (other.type === 2 && this.type === 1) {
                    this.type = 2;
                }
            }
        }
        // console.log(this._position)
        return this._position;
    }

    collision(other) {
        const pos1 = other._position;
        const size1 = other.size;
        const pos2 = this._position;
        const size2 = this.size;

        const left1 = pos1[0];
        const right1 = pos1[0] + size1;
        const top1 = pos1[1];
        const bottom1 = pos1[1] + size1;
        const left2 = pos2[0];
        const right2 = pos2[0] + size2;
        const top2 = pos2[1];
        const bottom2 = pos2[1] + size2;

        if (
            bottom1 < top2 ||
            top1 > bottom2 ||
            right1 < left2 ||
            left1 > right2
        ) {
            return false;
        }
        return true;
    }
}

var sqrs = [];

window.addEventListener("DOMContentLoaded", () => {
    console.log("hi");
    document.getElementById("canv").width = window.innerWidth;
    document.getElementById("canv").addEventListener("click", () => {
        sqrs = [];
    });
    window.addEventListener("resize", () => {
        document.getElementById("canv").width = window.innerWidth;
        sqrs = [];
    })
    setInterval(() => { main(document.getElementById("canv")) }, 10);
    setInterval(() => { updateCounter() }, 250);
})

function main(canv) {
    const ctx = canv.getContext("2d");
    if (ctx) {
        ctx.clearRect(0, 0, canv.width, canv.height);
        if (sqrs.length < 1) {
            for (let i = 0; i < 250; i++) {
                sqrs.push(new sqr(canv));
            }
        }
        for (let i = 0; i < sqrs.length; i++) {
            const element = sqrs[i];
            element.update();
            // ctx.fillStyle = "rgb(255 0 0)";
            if (element.type == 0) {
                ctx.fillStyle = "rgb(128 128 128)";
            } else if (element.type == 1) {
                ctx.fillStyle = "rgb(255, 255, 255)";
            }
            else {
                ctx.fillStyle = "rgb(255, 0, 0)";
            }
            const pos = element.position;
            ctx.fillRect(pos[0], pos[1], element.size, element.size);
        }
    }
    else {
        window.close(); // get screwed lmao
    }
}

function updateCounter()
{
    var left = [0,0,0]
    for (let i = 0; i < sqrs.length; i++) {
        left[sqrs[i].type] += 1;
    }
    document.getElementById("r").innerText = "rocks: " + left[0];
    document.getElementById("p").innerText = "papers: " + left[1];
    document.getElementById("s").innerText = "scissors: " + left[2];
}