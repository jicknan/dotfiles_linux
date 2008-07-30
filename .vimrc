" vim:shiftwidth=2:tabstop=8:expandtab
" ~/.vimrc file
"

" Use Vim settings, rather then Vi settings (much better!).
" This must be first, because it changes other options as a side effect.
set nocompatible
set wildmenu            " 自动补全命令时候使用菜单式匹配列表
set backspace=indent,eol,start	" backspace over everything in insert mode
"set mouse=a            " 启用鼠标
set autoindent		" always set autoindenting on
set showmatch		" 在输入括号时光标会短暂地跳到与之相匹配的括号处，不影响输入
set formatoptions+=mM	" 正确地处理中文字符的折行和拼接
set history=100		" keep 100 lines of command line history
set incsearch		" do incremental searching
set ruler		" always show the cursor position along the bottom
set showcmd		" display incomplete commands
set shiftwidth=4	" set autoindent step
set background=dark	" background you're used: dark | light
"colorscheme InkPot	" colorscheme
set number		" show line numbers
set winminheight=0      " win min heitht, default 1
"set path=/usr/include/*	" where gf, ^Wf, find will search
"set nobackup		" do not keep a backup file, use versions instead
set backup		" keep a backup file
set backupdir=~/.tmp	" put backup file here
set directory=~/.tmp	" put .swap file here
set fileencoding=utf-8	" default file encoding
set fileencodings=utf-8,gbk,ucs-bom,big5 " fileconding detection order
set termencoding=utf-8  " support Chinese display in rxvt-unicode
set ambiwidth=double    " 中文引号显示

" Switch syntax highlighting on, when the terminal has colors
" Also switch on highlighting the last used search pattern.
if &t_Co > 2 || has("gui_running")
  " 语法高亮
  syntax on
  " 搜索高亮
  set hlsearch
endif

set scrolloff=5	        " min lines to keep above and below the cursor

if has('multi_byte') && v:version > 601
  if v:lang =~? '^\(zh\)\|\(ja\)\|\(ko\)'
    set ambiwidth=double
  endif
endif

" Key mappings to ease browsing long lines
noremap  <C-J>       gj
noremap  <C-K>       gk
noremap  <Down>      gj
noremap  <Up>        gk
inoremap <Down> <C-O>gj
inoremap <Up>   <C-O>gk

" Key mapping to stop the search highlight
nmap <silent> <C-F2>      :nohlsearch<CR>
imap <silent> <C-F2> <C-O>:nohlsearch<CR>

" Key mapping for the taglist.vim plugin
nmap <C-F9>      :Tlist<CR>
imap <C-F9> <C-O>:Tlist<CR>

" Key mappings for quickfix commands
nmap <C-F11> :cn<CR>
nmap <C-F12> :cp<CR>

" Key mapping for switch between splits
"nmap <C-J> <C-W>j<C-W>_
"nmap <C-K> <C-W>k<C-W>_
"nmap <C-L> <C-W>L<bar>
"nmap <C-H> <C-W>H<bar>

" Only do this part when compiled with support for autocommands.
if has("autocmd")

  " Enable file type detection.
  " Use the default filetype settings, so that mail gets 'tw' set to 72,
  " 'cindent' is on in C files, etc.
  " Also load indent files, to automatically do language-dependent indenting.
  filetype plugin indent on

  " When editing a file, always jump to the last known cursor position.
  " Don't do it when the position is invalid or when inside an event handler
  " (happens when dropping a file on gvim).
  autocmd BufReadPost *
    \ if line("'\"") > 0 && line("'\"") <= line("$") |
    \   exe "normal g`\"" |
    \ endif

  " File type related autosetting
  autocmd FileType c,cpp setlocal textwidth=78
  autocmd FileType diff  setlocal shiftwidth=4
  autocmd FileType html  setlocal autoindent
  autocmd FileType sh setlocal textwidth=78
  autocmd FileType text setlocal fo+=ro textwidth=78 tabstop=4
  "autocmd FileType conf setlocal fo-=l textwidth=78
  " 让 python 展开Tab，显示行号，缩进4, Tab宽度4
  autocmd FileType python set et nu sw=4 ts=4 

  " Tags file
  autocmd BufEnter /home/jick/project/NS65/* setlocal tags+=/home/jick/project/NS65/tags
  autocmd BufEnter /home/jick/project/Linksys_SMB/* setlocal tags+=/home/jick/project/Linksys_SMB/tags
  autocmd BufEnter /home/jick/project/ns65.jick/* setlocal tags+=/home/jick/project/ns65.jick/tags
  autocmd BufEnter /home/jick/project/ns65.jick/linux-orion-git/* setlocal tags=/home/jick/project/ns65.jick/linux-orion-git/tags
  autocmd BufEnter /home/jick/project/pidgin-mtn/* setlocal tags+=/home/jick/project/pidgin-mtn/tags
  autocmd BufEnter /usr/src/linux/* setlocal tags+=/usr/src/linux/tags
endif " has("autocmd")

if !exists("auto_c")
    let auto_c=1
    au BufNewFile *.c 0r ~/.vim/files/c.skel
    "au BufNewFile *.c normal gnp 
    au BufNewFile *.h 0r ~/.vim/files/h.skel
    au BufNewFile *.sh 0r ~/.vim/files/sh.skel
    au BufNewFile Makefile 0r ~/.vim/files/makefile.skel
    au BufNewFile Rules.make 0r ~/.vim/files/Rules.make.skel
    au BufNewFile *.pl 0r ~/.vim/files/pl.skel
    autocmd BufNewFile *.py 0r ~/.vim/files/python.skel
    autocmd BufNewFile *.rst 0r ~/.vim/files/rst.skel
    ":%s/_filename_/\=bufname("%")
    :"%s/_datetime_/\=strftime("%c")
    map gse <ESC>:%s/_filename_/\=bufname("%")/<CR>:%s/_datetime_/\=strftime("%c")/<CR>
    map gse2 <ESC>:%s/_datetime_/\=strftime("%c")/<CR>
    au BufNewFile *.[ch] normal gse
    au BufNewFile *.sh normal gse
    au BufNewFile *.rst normal gse2
endif

" Highlight space errors in C/C++ source files (Vim tip #935)
if $VIM_HATE_SPACE_ERRORS != '0'
    let c_space_errors=1
endif

"set statusline=%<%f\ %h%m%r%=%k[%{(&fenc==\"\")?&enc:&fenc}%{(&bomb?\",BOM\":\"\")}]\ %-14.(%l,%c%V%)\ %P
"Format the statusline
"Nice statusbar
set laststatus=2
set statusline=
set statusline+=%2*%-3.3n%0*\ " buffer number
set statusline+=%f\ " file name
set statusline+=%h%1*%m%r%w%0* " flag
set statusline+=[
set statusline+=%{strlen(&ft)?&ft:'none'}, " filetype
set statusline+=%{&encoding}, " encoding
set statusline+=%{&fileformat}] " file format
set statusline+=%= " right align
"set statusline+=%2*0x%-8B\ " current char
set statusline+=0x%-8B\ " current char
set statusline+=%-14.(%l,%c%V%)\ %<%P " offset
