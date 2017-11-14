swtest
------
xv6の `swtch` の動作を理解するためのサンプルコード


## ビルド方法

```sh
$ make
```

xv6の `swtch.S` および `context` 構造体をそのまま流用しているため，32ビット(i386)用のコンパイラおよびライブラリが必要です．macOS (10.13.x) 上で動作を確認しています．

例えば64ビット版Ubuntuで動作させる場合は以下のようにして必要なライブラリを導入します．

```sh
$ apt-get install multilib
```

さらにLinuxで動作させるためには，`swtch.S` を編集してラベル `_swtch` を `swtch` に変更し，
`valloc` を `malloc` に変更する等の措置が必要となるかも知れません．

## 実行方法

```sh
$ ./swtest
foo: 0
bar: 0
baz: 0
foo: 1
bar: 2
baz: 3
foo: 2
bar: 4
baz: 6
foo: 3
bar: 6
baz: 9
...
```

```sh
$ ./schtest
foo: 0
bar: 0
baz: 0
foo: 1
bar: 2
baz: 3
foo: 2
bar: 4
baz: 6
foo: 3
bar: 6
baz: 9
...
```
