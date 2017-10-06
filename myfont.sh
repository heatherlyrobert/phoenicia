
cd /home/system/my_font*/
txt2bdf > shrike.bdf
bdftopcf -o shrike.pcf shrike.bdf
gzip -k -f shrike.pcf
cp shrike.pcf.gz /usr/share/fonts/misc/

cd /usr/share/fonts/misc/
chown root:root *
chmod 0755 *
rm -f fonts.dir
mkfontdir
mkfontscale
fc-cache -f -v
cd /home/system/my_font*/
