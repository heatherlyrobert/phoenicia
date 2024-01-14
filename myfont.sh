
## start in my_font
cd /home/system/phoenicia*/

## make the bdf version
echo  "txt2bdf shrike > shrike.bdf"
txt2bdf shrike > shrike.bdf
echo  "txt2bdf square > square.bdf"
txt2bdf square > square.bdf

## make the pcf version (from bdf)
echo "bdftopcf -o shrike.pcf shrike.bdf"
bdftopcf -o shrike.pcf shrike.bdf
echo "bdftopcf -o square.pcf square.bdf"
bdftopcf -o square.pcf square.bdf

## make the psf version (from bdf)
bdf2psf --fb shrike.bdf /usr/share/bdf2psf/standard.equivalents /usr/share/bdf2psf/ascii.set 256 shrike.psf
bdf2psf --fb square.bdf /usr/share/bdf2psf/standard.equivalents /usr/share/bdf2psf/ascii.set 256 square.psf

## put into console fonts directory
gzip -k -f shrike.psf
cp shrike.psf.gz /usr/share/consolefonts/
gzip -k -f square.psf
cp square.psf.gz /usr/share/consolefonts/

## put into shared fonts directory
gzip -k -f shrike.pcf
cp shrike.pcf.gz /usr/share/fonts/misc/
gzip -k -f square.pcf
cp square.pcf.gz /usr/share/fonts/misc/


## make all readable
cd /usr/share/fonts/misc/
chown root:root *
chmod 0755 *

## update cache
rm -f fonts.dir
mkfontdir
mkfontscale
fc-cache -f -v

## return to my_font
cd /home/system/phoenicia*/

## create txf version of shrike
txt2txf


