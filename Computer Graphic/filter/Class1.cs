using System.Drawing;
using System;
using System.Xml.Linq;

namespace filter
{
    public class Filter
    {
        public static int Clamp(int value, int min, int max)
        {
            return Math.Min(Math.Max(value, min), max);
        }
        public static int[,] Gx = {
            { -1, 0, 1 },
            { -2, 0, 2 },
            { -1, 0, 1 }
        };
        public static int[,] Gy = {
            { -1, -2, -1 },
            { 0, 0, 0 },
            { 1, 2, 1 }
        };
        public static Bitmap Execute(Bitmap source)
        {
            Bitmap filteredImage = new Bitmap(source.Width, source.Height);
            for (int x = 0; x < source.Width; x++)
            {
                for (int y = 0; y < source.Height; y++)
                {
                    int radiusX = 1, radiusY = 1;
                    float resultRX = 0, resultGX = 0, resultBX = 0, resultRY = 0, resultGY = 0, resultBY = 0;
                    for (int i = -radiusY; i <= radiusY; i++)
                        for (int j = -radiusX; j <= radiusX; j++)
                        {
                            int idX = Clamp(x + j, 0, source.Width - 1);
                            int idY = Clamp(y + i, 0, source.Height - 1);
                            Color Color = source.GetPixel(idX, idY);
                            resultRX += Color.R * Gx[j + radiusX, i + radiusY];
                            resultGX += Color.G * Gx[j + radiusX, i + radiusY];
                            resultBX += Color.B * Gx[j + radiusX, i + radiusY];
                            resultRY += Color.R * Gy[j + radiusX, i + radiusY];
                            resultGY += Color.G * Gy[j + radiusX, i + radiusY];
                            resultBY += Color.B * Gy[j + radiusX, i + radiusY];
                        }
                    int resultR = Clamp((int)Math.Sqrt(Math.Pow(resultRX, 2.0) + Math.Pow(resultRY, 2.0)), 0, 255);
                    int resultG = Clamp((int)Math.Sqrt(Math.Pow(resultGX, 2.0) + Math.Pow(resultGY, 2.0)), 0, 255);
                    int resultB = Clamp((int)Math.Sqrt(Math.Pow(resultBX, 2.0) + Math.Pow(resultBY, 2.0)), 0, 255);

                    Color newPixel = Color.FromArgb(Clamp(resultR, 0, 255), Clamp(resultG, 0, 255), Clamp(resultB, 0, 255));
                    filteredImage.SetPixel(x, y, newPixel);
                }
            }
            return filteredImage;
        }
    }
}