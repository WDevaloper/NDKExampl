package com.youbesun.myapplication

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import javax.microedition.khronos.opengles.GL10
import java.nio.ByteBuffer.allocateDirect
import java.nio.ByteOrder
import java.nio.FloatBuffer


class MeGLSurfaceView(context: Context?, attrs: AttributeSet?) : GLSurfaceView(context, attrs) {
    private var mVB: FloatBuffer? = null
    private val coords = floatArrayOf(
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f
    )

    init {
        setRenderer(MyRender())
        val vbb = allocateDirect(coords.size * 4)
        vbb.order(ByteOrder.nativeOrder())
        mVB = vbb.asFloatBuffer()
        mVB?.put(coords)
        mVB?.position(0)
    }


    private inner class MyRender : Renderer {
        override fun onSurfaceCreated(gl: GL10, config: javax.microedition.khronos.egl.EGLConfig?) {
            gl.glEnableClientState(GL10.GL_VERTEX_ARRAY)
        }


        override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
            gl.glViewport(0, 0, width, height)
        }

        override fun onDrawFrame(gl: GL10) {
            gl.glClear(GL10.GL_COLOR_BUFFER_BIT or GL10.GL_DEPTH_BUFFER_BIT)
            gl.glClearColor(1.0f, 1.0f, 1.0f, 1.0f)
            gl.glColor4f(1.0f, 0.0f, 0.0f, 1.0f)
            gl.glVertexPointer(3, GL10.GL_FLOAT, 0, mVB)
            gl.glDrawArrays(GL10.GL_TRIANGLES, 0, 6)
        }
    }
}