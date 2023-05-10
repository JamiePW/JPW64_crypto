import java.math.*;

public class sbox_generator {
    //public static int poly = 0x11b;
    public static int poly = 0x163;

    /**AES使用的不可约多项式表示为0x11b，十进制表示为283
     * 本算法使用的不可约多项式表示为0x163，十进制表示为355
     * **/

    public static void main (String[] agrs) {
        int i, j, k;
        int[] tem1 = new int[8];
        int[] tem2 = new int[8];    //tem1和tem2负责实现字节变换，存储每个字节的八个比特位并进行运算
        int[][] Sbox = new int[16][16];
        int[][] invSbox = new int[16][16];

        for (i=0;i<16;i++) {
            for (j=0;j<16;j++) {
                //输入初始数据
                Sbox[i][j] = (i<<4) + j;
                invSbox[i][j] = (i<<4) + j;

                /**先产生Sbox**/
                //求逆
                if (Sbox[i][j] != 0)
                    Sbox[i][j] = gf_exgcd(Sbox[i][j], poly)[1];


                //仿射变换
                for (k=0;k<8;k++)
                    tem1[k] = (Sbox[i][j] & (1<<k)) >> k;

                tem2[0] = tem1[0] ^ tem1[4] ^ tem1[5] ^ tem1[6] ^ tem1[7] ^ 0;
                tem2[1] = tem1[0] ^ tem1[1] ^ tem1[5] ^ tem1[6] ^ tem1[7] ^ 1;
                tem2[2] = tem1[0] ^ tem1[1] ^ tem1[2] ^ tem1[6] ^ tem1[7] ^ 1;
                tem2[3] = tem1[0] ^ tem1[1] ^ tem1[2] ^ tem1[3] ^ tem1[7] ^ 0;
                tem2[4] = tem1[0] ^ tem1[1] ^ tem1[2] ^ tem1[3] ^ tem1[4] ^ 1;
                tem2[5] = tem1[1] ^ tem1[2] ^ tem1[3] ^ tem1[4] ^ tem1[5] ^ 0;
                tem2[6] = tem1[2] ^ tem1[3] ^ tem1[4] ^ tem1[5] ^ tem1[6] ^ 0;
                tem2[7] = tem1[3] ^ tem1[4] ^ tem1[5] ^ tem1[6] ^ tem1[7] ^ 1;

                /**AES异或时使用的常量为0x63，即0b01100011，该数保证生成的Sbox具有某些安全性质
                 * 本算法使用的常量为0x96，即0b10010110
                 * **/

                Sbox[i][j] = 0;
                for (k=0;k<8;k++)
                    Sbox[i][j] = Sbox[i][j] + (tem2[k] << k);

            }
        }

        /**产生逆Sbox**/
        for (i=0;i<16;i++) {
            for (j=0;j<16;j++) {
                invSbox[Sbox[i][j] >> 4][Sbox[i][j] & 0xf] = (i << 4) + j;
            }
        }


        System.out.println("Sbox:");
        for (i=0;i<16;i++) {
            for (j=0;j<16;j++)
                System.out.printf("0x%02x, ", Sbox[i][j]);
            System.out.printf("\n");
        }

        System.out.println("invSbox:");
        for (i=0;i<16;i++) {
            for (j=0;j<16;j++)
                System.out.printf("0x%02x, ", invSbox[i][j]);
            System.out.printf("\n");
        }
    }

    //以下是有限域求逆函数，本质上就是扩展欧氏算法
    public static int[] gf_exgcd (int a, int b){
        int gcd, temx, temy;//gcd表示最终结果，temx，temy分别为递归过程中的中间变量
        int x, y;//x和y代表计算过程中的系数
        int[] tem;//tem用来存储递归过程的中间结果

        if (b == 0)
            return new int[]{a, 1, 0};
        else {
            tem = gf_exgcd(b, mod(a, b));
            gcd = tem[0];
            temx = tem[1];
            temy = tem[2];

            x = temy;
            y = temx^multiply(temy, divide(a, b));
            return new int[]{gcd, x, y};
        }

    }

    //以下算法实现了有限域下的模运算
    public static int mod (int a, int b) {
        int len1, len2, len;

        len1 = Integer.toBinaryString(a).length();
        len2 = Integer.toBinaryString(b).length();
        len = len1 - len2 + 1;

        if (len < 1) return a;

        else if (len == 1) return a^b;

        else if (len > 1){
            while (len1 >= len2){
                a ^= (b << (len1 - len2));
                len1 = Integer.toBinaryString(a).length();
                if (a == 0)
                    break;
            }
            return a;
        }
        return -1;
    }

    //以下引用了有限域的除法
    public static int divide (int a, int b){
        //len1为a二进制长度，len2为b二进制长度，len为二者之差
        int len1, len2, len;
        int div;//div是被除数位数大于除数时用于表示结果
        len1 = Integer.toBinaryString(a).length();
        len2 = Integer.toBinaryString(b).length();
        len = len1 - len2 + 1;

        //如果被除数位数小于除数，则直接返回0
        if (len<1) return 0;

            //如果二者位数相同，由二进制可知，商必为1
        else if (len == 1) return 1;

        else if (len > 1){
            div = 0;
            while (len1 >= len2){
                a ^= (b << (len1 - len2));
                div ^= (1 << (len1 - len2));
                len1 = Integer.toBinaryString(a).length();
                if (a ==0)
                    break;
            }
            return div;
        }
        return -1;
    }

    //以下调用了有限域的乘法
    public static int multiply (int a, int b){
        int result = 0;

        while (b>0){
            if (b%2 == 1)
                result ^= a;
            a = gmul(a, poly);
            b >>= 1;
        }

        return result;
    }

    //计算乘法中间结果
    public static int gmul (int a, int p){
        a <<= 1;
        if ((a&0x100) == 0x100)
            a ^= p;
        return (a&0xff);
    }
}
