# Bad USB

挿すと任意のファイルをgistに挙げられるBadUSB

**悪用厳禁**


1. `githubAPI`をgistのみチェックを入れて取得する
2. `gist.py`の`API_TOKEN`に`1`で取得したTOKENを入力
3. `gist.py`をsecret gistとして登録する
4. 登録した`gist id`を`d.c`の2箇所に書く
5. `write_badusb.sh`でチップに書き込み
  - ` scp d.c avr:~/ && ssh avr "sh write_badusb.sh d.c"`
6. usbを挿す
