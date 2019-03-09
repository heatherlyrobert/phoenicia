
## start in my_font
cd /home/system/phoenicia*/

## make the bdf version
txt2bdf > shrike.bdf

## make the pcf version (from bdf)
bdftopcf -o shrike.pcf shrike.bdf

## put into console fonts directory
gzip -k -f shrike.pcf
cp shrike.pcf.gz /usr/share/fonts/misc/
gzip -k -f shrike.psf
cp shrike.psf.gz /usr/share/consolefonts/

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

