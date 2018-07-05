rm -rf debops.zip && zip -r debops.zip . -x *.git* --exclude=*secret* -x UPGRADE-0.* --exclude=Makefile -x LICENSE -x CHANGES.rst -x wpinstaller.c -x ansible.cfg 


