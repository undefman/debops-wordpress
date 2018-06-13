
Bên máy Debops gõ lệnh:

ssh-keygen

enter cho tới khi kết thúc.

cat ~/.ssh/id_rsa.pub

Copy nội dung file đó vào bộ nhớ.


Bên máy wordperss gõ lệnh:

ssh-keygen

Nhấn enter cho tới khi lệnh hoàn thành.

gõ tiếp lệnh:

nano ~/.ssh/authorized_keys

dán nội dung copy ở trên vào cuối file.


Nhấn control + O (chữ O)

Nhấn tiếp Enter để save.

Nhấn control + X để thoát.



Gõ tiếp lệnh:

apt update && ap apt dist-upgrade && reboot

Chờ nó chạy xong, chờ vps wordpress reboot xong mới làm tiếp.


***


Bên máy Debops, gõ lệnh:

ssh root@ip.cua.may.wordpress

Nếu nó hỏi Are you sure you want to continue connecting (yes/no)?
thì gõ yes rồi enter.

nếu ssh kết nối mà ko hỏi password là ok.

Nếu ssh ok thì gõ exit để thoát ssh và tiếp tục tới bước *****

Nếu ssh ko được (do nó hỏi password) thì nhấn control + C vài lần để cancel. Liên hệ tui để được hổ trợ.


*****

Gõ lệnh cài chương trình cần thiết (chỉ cần làm 1 lần đầu.)

apt install git screen unzip libsasl2-dev python-dev libldap2-dev libssl-dev python-pip

pip install --upgrade pip

sudo pip install ansible debops passlib pycrypto

sudo debops-update



Chép file debops.zip lên máy Debops lưu và thư mục nào đó ví dụ:

/root/debops.zip (nếu đã chép rồi thì thôi.)

Gõ lệnh vào màn hình screen (để khi dis ssh, login lại thì vào lại màn hình đang chạy)

screen -xRD (nhấn enter nếu nó hỏi.)(mỗi khi ssh vào thì cứ gõ cái này trước rồi hãy làm việc)


Gõ lệnh giải nén:


cd /root/ && unzip debops.zip -d yourdomain.com



Chuyển vào thư mục vừa được giải nén.

cd yourdomain.com


Gõ tiếp:

git reset –hard && git fetch && git pull




Gõ lệnh:
./wpinstaller yourdomain.com 1


Nếu ko lỗi gì (lệnh kết thúc như hình trên) thì gõ tiếp:

./wpinstaller yourdomain.com 2


Nếu ko lỗi gì thì gõ tiếp:

./wpinstaller yourdomain.com 3



Nếu ko lỗi gì thì ok. Vào https://yourdomain.com xem ok chưa.




Login wordpress:
username là: admin
passowrd gõ lệnh: cat secret/wordpress/teehamster.us/credentials/admin/password

Login database:
username: wordpress
password gõ lệnh: cat secret/mariadb/teehamster.us/credentials/wordpress/password
