" Morgen Matvey http://snowarch.blogspot.com
"
" Vundle required config
set nocompatible              " be iMproved, required
filetype off                  " required
 
" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" " let Vundle manage Vundle, required
Plugin 'gmarik/Vundle.vim'
 
" User defined plugins
Plugin 'SirVer/ultisnips'
Plugin 'honza/vim-snippets'
Plugin 'scrooloose/nerdtree'
Plugin 'Rip-Rip/clang_complete'
Plugin 'c.vim'
Plugin 'octol/vim-cpp-enhanced-highlight'
Plugin 'vhdirk/vim-cmake'


" " All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required
" Put your non-Plugin stuff after this line
" 
 
" Игнорировать регистр при поиске
set ic
" Подсвечивать поиск
set hls
" Использовать инкреминтированный поиск
set is
" ширина текста 
set textwidth=120


 let &path.="src/include,src"


" Не делать все окна одинакового размера
set noequalalways
" Высота окон по-умолчанию 20 строк
set winheight=20
" задать размер табуляции в два пробела
set ts=2
" автоматически расставлять отступы
set autoindent
" Подсвечивать синтаксис
syntax on
" показывать номера строк
set number 
set tabstop=2
set fileencoding=utf-8
set shiftwidth=2
set smartindent
" Заменять табуляцию на пробелы
set expandtab
 
" Включаем bash-подобное дополнение командной строки
set wildmode=longest:list,full
 
" Подсвечивать 80 стобец
let &colorcolumn=&textwidth
highlight ColorColumn ctermbg=darkgray
 
" С/C++ файлы
autocmd filetype c,cpp set cin
 
" make-файлы
" В make-файлах нам не нужно заменять табуляцию пробелами
autocmd filetype make set noexpandtab
autocmd filetype make set nocin
 
" html-файлы
" Не расставлять отступы в стиле С в html файлах
autocmd filetype html set noexpandtab
autocmd filetype html set nocin
autocmd filetype html set textwidth=160
 
" css-файлы
" Не расставлять отступы в стиле C и не заменять табуляцию пробелами
autocmd filetype css set nocin
autocmd filetype css set noexpandtab
 
" python-файлы
" Не расставлять отступы в стиле С
autocmd filetype python set nocin
 
" Позволим конфигурационным файлам в проекте изменять настройки vim'a
set exrc
set secure
 
"Clang-completer
let g:clang_library_path = '/usr/lib/x86_64-linux-gnu/libclang-10.so.1'
" Включить дополнительные подсказки (аргументы функций, шаблонов и т.д.)
let g:clang_snippets=1
" Использоать ultisnips для дополнительных подскахок (чтобы подсказки шаблонов
" автогенерации были в выпадающих меню)
let g:clang_snippets_engine = 'ultisnips'
" Периодически проверять проект на ошибки
let g:clang_periodic_quickfix=1
" Подсвечивать ошибки
let g:clang_hl_errors=1
" Автоматически закрывать окно подсказок после выбора подсказки
let g:clang_close_preview=1
" По нажатию Ctrl+F проверить поект на ошибки
map <C-F> :call g:ClangUpdateQuickFix()<CR>
 
" Configure Nerdtree
map <C-n> :NERDTreeToggle<CR>
autocmd StdinReadPre * let s:std_in=1
autocmd VimEnter * if argc() == 0 && !exists("s:std_in") | NERDTree | endif
set splitright
 
" Snippets
let g:UltiSnipsExpandTrigger="<C-a>"
let g:UltiSnipsListSnippets="<C-d>"
let g:UltiSnipsJumpForwardTrigger="<C-b>"
let g:UltiSnipsJumpBackwardTrigger="<C-z>"
let g:UltiSnipsEditSplit="vertical"
let g:UltiSnipsUsePythonVersion=2
