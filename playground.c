temporaryImage[i][j].rgbTempRed = image[i][j].rgbTempRed;
image[i][j].rgbTempRed = image[i][width - j - 1].rgbTempRed;
image[i][width - j - 1].rgbTempRed = temporaryImage[i][j].rgbTempRed;

temporaryImage[i][j].rgbTempBlue = image[i][j].rgbTempBlue;
image[i][j].rgbTempBlue = image[i][width - j - 1].rgbTempBlue;
image[i][width - j - 1].rgbTempBlue = temporaryImage[i][j].rgbTempBlue;

temporaryImage[i][j].rgbTempGreen = image[i][j].rgbTempGreen;
image[i][j].rgbTempGreen = image[i][width - j - 1].rgbTempGreen;
image[i][width - j - 1].rgbTempGreen = temporaryImage[i][j].rgbTempGreen;