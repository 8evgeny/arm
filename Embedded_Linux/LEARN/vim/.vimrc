
set nu
set nocompatible
filetype off
" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()



" " let Vundle manage Vundle, required
Plugin 'gmarik/Vundle.vim'

" User defined plugins
"Plugin 'SirVer/ultisnips'                                                     
"Plugin 'honza/vim-snippets'                                                    
"Plugin 'scrooloose/nerdtree'
"Plugin 'Rip-Rip/clang_complete'

"set tabstop=4
"set softtabstop=4
"set shiftwidth=4
"set noexpandtab
"set colorcolumn=110
"highlight ColorColumn ctermbg=darkgray
"augroup project
"    autocmd!
"    autocmd BufRead,BufNewFile *.h,*.c set filetype=c.doxygen
"augroup END
"let &path.="src/include,/usr/include/AL,"
"set includeexpr=substitute(v:fname,'\\.','/','g')
"set makeprg=make\ -C\ build\ -j9
"nnoremap <F4> :make!<cr>
