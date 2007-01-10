" vim:shiftwidth=2:tabstop=8:expandtab
" ~/.vimrc file

if has('gui_running')
  let do_syntax_sel_menu=1
endif

if has('gui_running') && $LANG !~ '\.'
  set encoding=utf-8
endif

set nocompatible	" this must be first
set backspace=indent,eol,start	" backspace over everything in insert mode
set autoindent		" always set autoindenting on
set showmatch		" 在输入括号时光标会短暂地跳到与之相匹配的括号处，不影响输入
set formatoptions+=mM	" 正确地处理中文字符的折行和拼接
set statusline=%<%f\ %h%m%r%=%k[%{(&fenc==\"\")?&enc:&fenc}%{(&bomb?\",BOM\":\"\")}]\ %-14.(%l,%c%V%)\ %P
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
set backup		" keep a backup file
set backupdir=~/.tmp	" put backup file here
set directory=~/.tmp	" put .swap file here
set fileencoding=utf-8	" default file encoding
set fileencodings=ucs-bom,utf-8,gbk,big5
set termencoding=utf-8

" Switch syntax highlighting on, when the terminal has colors
" Also switch on highlighting the last used search pattern.
if &t_Co > 2 || has("gui_running")
  syntax on
  set hlsearch
endif

"if has('mouse')
"    set mouse=a	" use mouse everywhere
"endif
set scrolloff=10	" min lines to keep above and below the cursor

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
nmap <C-J> <C-W>j<C-W>_
nmap <C-K> <C-W>k<C-W>_
nmap <C-L> <C-W>L<bar>
nmap <C-H> <C-W>H<bar>

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
"  autocmd FileType conf setlocal fo-=l textwidth=78

  " Tags file
  autocmd BufEnter /work/WNS54/* setlocal tags+=/work/WNS54/tags
  autocmd BufEnter /work/WNS54_sitsang/* setlocal tags+=/work/WNS54_sitsang/tags
  autocmd BufEnter /work/simple_nas/* setlocal tags+=/work/simple_nas/tags
  autocmd BufEnter /usr/src/linux/* setlocal tags+=/usr/src/linux/tags
  autocmd BufEnter /work/redboot/* setlocal tags+=/work/redboot/tags
endif " has("autocmd")

if !exists("auto_c")
    let auto_c=1
    au BufNewFile *.info 0r ~/.vim/files/info.skel
    au BufNewFile *.SlackBuild 0r ~/.vim/files/SlackBuild.skel
    au BufNewFile *.c 0r ~/.vim/files/c.skel
    "au BufNewFile *.c normal gnp 
    au BufNewFile *.h 0r ~/.vim/files/h.skel
    au BufNewFile *.sh 0r ~/.vim/files/sh.skel
    ":%s/_filename_/\=bufname("%")
    :"%s/_datetime_/\=strftime("%c")
    au BufNewFile *.pl 0r ~/.vim/files/pl.skel
    ":%s/_filename_/\=bufname("%")
    :"%s/_datetime_/\=strftime("%c")
    map gse <ESC>:%s/_filename_/\=bufname("%")/<CR>:%s/_datetime_/\=strftime("%c")/<CR>
    au BufNewFile *.[ch] normal gse
    au BufNewFile *.sh normal gse
endif

" Highlight space errors in C/C++ source files (Vim tip #935)
if $VIM_HATE_SPACE_ERRORS != '0'
    let c_space_errors=1
endif
