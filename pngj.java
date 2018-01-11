package example;

import android.content.res.AssetManager;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.util.Arrays;
import java.util.Random;

import ar.com.hjg.pngj.ImageLineByte;
import ar.com.hjg.pngj.ImageLineInt;
import ar.com.hjg.pngj.PngReader;
import ar.com.hjg.pngj.PngReaderByte;

import static junit.framework.Assert.assertEquals;
import static junit.framework.Assert.assertNotNull;

/**
 * Created by alchera on 18. 1. 11.
 */

class FrameData
{
//    int format; // Always ARGB32
    int width, height;
    int channel;
    byte[] data;
}

public class LoadTest extends TestBackbone {

    FrameData lhs,rhs;
    PngReaderByte pngl, pngr;
    AssetManager am;

    @Before
    public void LoadImage1() throws Exception{
        String filename = "cat.png";
        lhs=new FrameData();

        am=context.getAssets();
        pngl = new PngReaderByte(am.open(filename));
        lhs.channel = pngl.imgInfo.channels;

        lhs.width=pngl.imgInfo.cols;
        lhs.height=pngl.imgInfo.rows;
        lhs.data = new byte[lhs.width*lhs.height*lhs.channel*lhs.channel];

        Assert.assertNotNull(lhs);
        Assert.assertNotNull(lhs.data);

        for(int i=0;i<lhs.height*lhs.channel;i++) {
            ImageLineByte line = pngl.readRowByte();
            byte[] line1 = line.getScanlineByte();

            lhs.data[(line1.length)*i]=line1[0];
            System.arraycopy(line1,0,lhs.data,(line1.length)*i,line1.length);
        }

        assertNotNull(lhs);
    }

    @Before
    public void LoadImage2() throws Exception{
        String filename = "cat_flip.png";
        rhs=new FrameData();
        am=context.getAssets();
        pngr = new PngReaderByte(am.open(filename));
        rhs.channel = pngr.imgInfo.channels;

        rhs.width=pngr.imgInfo.cols;
        rhs.height=pngr.imgInfo.rows;
        rhs.data = new byte[rhs.width*rhs.height*rhs.channel*rhs.channel];

        Assert.assertNotNull(rhs);
        Assert.assertNotNull(rhs.data);

        for(int i=0;i<rhs.height*rhs.channel;i++) {
            ImageLineByte line = pngr.readRowByte();
            byte[] line1 = line.getScanlineByte();

            rhs.data[(line1.length)*i]=line1[0];
            System.arraycopy(line1,0,rhs.data,(line1.length)*i,line1.length);
        }
        ;
        assertNotNull(rhs);
    }

    @Test
    public void CheckSize(){
        assertEquals(lhs.width, rhs.width);
        assertEquals(lhs.height, rhs.height);
    }

    @Test
    public void EnsureChan4(){
        assertEquals(4, rhs.channel);
        assertEquals(4, lhs.channel);
    }

    @Test
    public void CheckData(){
        Random rng = new Random();

        int length = lhs.width * rhs.height * lhs.channel * lhs.channel;
        int count = 16;

        while(count-- > 0){
            int idx = rng.nextInt(length - 1);
            int ridx = length - idx - 1;
            Assert.assertEquals(lhs.data[idx], rhs.data[ridx]);
        }
    }

//    @Test
//    public void CheckData2(){
//        Random rng = new Random();
//
//        int length = lhs.width * rhs.height * lhs.channel;
//        int count = 16;
//
//        while(count-- > 0){
//            int idx = rng.nextInt(length - 1);
//            int ridx = 521*((idx/512)+1)-idx%2;
//
//            Assert.assertEquals(lhs.data[idx], rhs.data[ridx]);
//        }
//    }
}
