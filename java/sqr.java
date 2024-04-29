package com.rps;

import java.util.Random;
import java.awt.Rectangle;

public class sqr {
    public float x;
    public float y;
    public float vx;
    public float vy;
    public float s;
    public int type;

    public sqr() {
        Random r = new Random();
        this.x = r.nextInt(190) - 95;
        this.y = r.nextInt(190) - 95;
        this.vx = r.nextFloat() - .5f;
        this.vy = r.nextFloat() - .5f;
        this.s = 1;
        this.type = r.nextInt(3);
    }

    public void update() {
        this.x += this.vx;
        this.y += this.vy;
        if (this.x > 95 || this.x < -95)
            this.vx *= -1;
        if (this.y > 95 || this.y < -95)
            this.vy *= -1;
    }

    // TODO: fix this function,
    // it works but only when the squares interact in a specific way
    public boolean col(sqr other) {
        Rectangle r1 = new Rectangle((int) other.x + (int) (other.s / 2), (int) other.y + (int) (other.s / 2),
                (int) other.x - (int) (other.s / 2), (int) other.y - (int) (other.s / 2));
        Rectangle r2 = new Rectangle((int) this.x + (int) (this.s / 2), (int) this.y + (int) (this.s / 2),
                (int) this.x - (int) (this.s / 2), (int) this.y - (int) (this.s / 2));
        if (r1.intersects(r2)) {
            return true;
        }
        return false;
    }
}
