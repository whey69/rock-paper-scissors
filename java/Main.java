package com.rps;

import org.lwjgl.glfw.*;
import org.lwjgl.opengl.*;
import org.lwjgl.system.*;

import java.nio.*;

import static org.lwjgl.glfw.Callbacks.*;
import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryStack.*;
import static org.lwjgl.system.MemoryUtil.*;

public class Main {
    private static long window;
    private static int width = 720;
    private static int height = 720;
    private static sqr[] sqrs = new sqr[100];

    public static void main(String[] args) {
        // System.out.println("hi");

        for (int i = 0; i < sqrs.length; i++) {
            sqrs[i] = new sqr();
        }

        init();
        loop();

        glfwFreeCallbacks(window);
        glfwDestroyWindow(window);

        glfwTerminate();
        glfwSetErrorCallback(null).free();
    }

    private static void init() {
        GLFWErrorCallback.createPrint(System.err).set();

        if (!glfwInit()) {
            throw new IllegalStateException("glfw init failed");
        }

        // glfwDefaultWindowHints();
        // glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(width, height, "rps", NULL, NULL);
        if (window == NULL) {
            throw new RuntimeException("failed at creating window");
        }

        glfwSetKeyCallback(window, (window, key, scancode, action, mods) -> {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
                glfwSetWindowShouldClose(window, true);
            // this probably isnt the right place to handle this
            if (key == GLFW_KEY_SPACE) {
                for (int i = 0; i < sqrs.length; i++) {
                    sqrs[i] = new sqr();
                }
            }
        });

        try (MemoryStack stack = stackPush()) {
            IntBuffer pWidth = stack.mallocInt(1); // aka c++'s int* pWidth
            IntBuffer pHeight = stack.mallocInt(1);

            glfwGetWindowSize(window, pWidth, pHeight);
            GLFWVidMode vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

            glfwSetWindowPos(window, (vidMode.width() - pWidth.get(0)) / 2, (vidMode.height() - pHeight.get(0)) / 2);
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        glfwShowWindow(window);
    }

    private static void loop() {
        GL.createCapabilities();

        glClearColor(0f, 0f, 0f, 0f);

        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            for (sqr s : sqrs) {
                s.update();
                drawsqr(s.x / 100, s.y / 100, s.s / 10, s.type);

                for (sqr s2 : sqrs) {
                    if (s != s2 && s.col(s2)) {
                        if (s2.type == 0 && s.type == 2) {
                            s.type = 0;
                        }
                        if (s2.type == 1 && s.type == 0) {
                            s.type = 1;
                        }
                        if (s2.type == 2 && s.type == 1) {
                            s.type = 2;
                        }
                    }
                }
            }
            // drawsqr(0, 0, .1f, 1);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    private static void drawsqr(float x, float y, float s, int c) {
        // GL11.glColor3f(255, 255 * c, 255 * c);
        if (c == 0) {
            GL11.glColor3f(.5f, .5f, .5f);
        } else if (c == 1) {
            GL11.glColor3f(1, 1, 1);
        } else if (c == 2) {
            GL11.glColor3f(1, 0, 0);
        } else {
            System.out.println(c);
            GL11.glColor3f(0, 0, 1);
        }

        glBegin(GL_QUADS);

        float h = s / 2f;

        glVertex2f(x - h, y + h);
        glVertex2f(x + h, y + h);
        glVertex2f(x + h, y - h);
        glVertex2f(x - h, y - h);

        glEnd();
    }
}
