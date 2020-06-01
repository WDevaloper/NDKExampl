package com.youbesun.myapplication

import android.content.Context
import android.graphics.Color
import android.graphics.Paint
import android.util.AttributeSet
import android.view.SurfaceHolder
import android.view.SurfaceView
import android.view.Surface


class MySurfaceView @JvmOverloads constructor(
    context: Context, attrs: AttributeSet? = null, defStyleAttr: Int = 0
) : SurfaceView(context, attrs, defStyleAttr), SurfaceHolder.Callback {
    private lateinit var mDrawThread: DrawThread

    init {
        holder.addCallback(this)
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, width: Int, height: Int) {
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        mDrawThread = DrawThread(holder.surface)
        mDrawThread.start()
    }


    private class DrawThread internal constructor(private val mSurface: Surface) : Thread() {
        private var mRunning = true
        private val mPaint = Paint().also { it.color = Color.RED }
        private var right: Float = 100f

        override fun run() {
            while (mRunning) {
                val canvas = mSurface.lockCanvas(null)

                canvas.drawColor(Color.WHITE)
                canvas.drawRect(0f, 0f, right, 100f, mPaint)
                mSurface.unlockCanvasAndPost(canvas)

                try {
                    sleep(50)
                    if (right > 200) {
                        right = 100f
                    }
                    right += 10
                } catch (e: InterruptedException) {
                    e.printStackTrace()
                }

            }
        }
    }

}