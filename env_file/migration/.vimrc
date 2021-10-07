" - For Neovim: stdpath('data') . '/plugged'
" - Avoid using standard Vim directory names like 'plugin'
call plug#begin('~/.vim/plugged')
" Make sure you use single quotes

" Shorthand notation; fetches https://github.com/junegunn/vim-easy-align
Plug 'junegunn/vim-easy-align'

" Any valid git URL is allowed
Plug 'https://github.com/junegunn/vim-github-dashboard.git'

" Multiple Plug commands can be written in a single line using | separators
Plug 'SirVer/ultisnips' | Plug 'honza/vim-snippets'

" On-demand loading
Plug 'scrooloose/nerdtree', { 'on':  'NERDTreeToggle' }
"Plug 'tpope/vim-fireplace', { 'for': 'clojure' }

" Using a non-default branch
" Plug 'rdnetto/YCM-Generator', { 'branch': 'stable' }

" Using a tagged release; wildcard allowed (requires git 1.9.2 or above)
" Plug 'fatih/vim-go', { 'tag': '*' }

" Plugin options
Plug 'nsf/gocode', { 'tag': 'v.20150303', 'rtp': 'vim' }

" Plugin outside ~/.vim/plugged with post-update hook
Plug 'junegunn/fzf', { 'dir': '~/.fzf', 'do': './install --all' }

" Unmanaged plugin (manually installed and updated)
Plug '~/my-prototype-plugin'

" under & top status bar
Plug 'vim-airline/vim-airline'
Plug 'vim-airline/vim-airline-themes'

" prompt in terminal
Plug 'edkolev/promptline.vim'

" Plugin Tagbar
Plug 'majutsushi/tagbar'

" vim fugitive
" Plug 'tpope/vim-fugitive'
" YouCompleteMe(YCM) for vim
" Plug 'valloric/youcompleteme'

" A light and configurable statusline/tabline plugin for Vim
"Plug 'itchyny/lightline.vim'

" theme apply
"Plug 'junegunn/seoul256.vim'
"Plug 'altercation/vim-colors-solarized'

" Initialize plugin system
call plug#end()

set autoindent
set cindent
set smartindent
set nocompatible
set visualbell
set backspace=indent,eol,start
set history=50
set ruler
set showcmd
set incsearch
set tabstop=4
set shiftwidth=4
set number
set nobackup
set smartindent
set incsearch
set hlsearch
"space to tab - noexpandtab
set noexpandtab
"tab to space - expandtab
"set expandtab

"set mouse=a"

set ts=4
set sw=4
set sm
set nu
set bg=dark

if has("syntax")
syntax on
endif

syntax on "syntax higlighting"

"=setup easy to write program="
filetype plugin on

"set tags+=/usr/include/tags,/tags"

set encoding=utf-8

"============setup for ctags=============="
set tags=/home/worker/tags/tags

"============setup for cscope ============"
set csprg=/usr/bin/cscope
set csto=0
set cst
set nocsverb

if filereadable("./cscope.out")
	cs add cscope.out
else
	cs add /home/worker/tags/cscope.out
endif
set csverb

"source ~/.vim/plugin/cscope_maps.vim

"=============setup for tag list=========="
"filetype on
"nmap <F7> :TlistToggle<CR>
"let Tlist_Ctags_Cmd = "/usr/bin/ctags"
"let Tlist_Inc_Winwidth = 0
"let Tlist_Exit_OnlyWindow = 0
"let Tlist_Auto_Open = 0
"let Tlist_Use_Right_Window = 1

"let Tlist_Auto_Highlight_Tag = 1
"let Tlist_Auto_Update = 1
"let Tlist_Exit_OnlyWindow = 1
"let Tlist_File_Fold_Auto_Close = 1
"let Tlist_Highlight_Tag_On_BufEnter = 1
"let Tlist_Use_Right_Window = 1
"let Tlist_Use_SingleClick = 1

"============setup for NERDTree============="
"let NERTreeWinPos = "left"
nmap <F5> :NERDTreeToggle<CR>

"============setup for TagBar==============="
nmap <F8> :TagbarToggle<CR>

"============Setup for Source Exploer====================="
"nmap <F8> :SrcExplToggle<CR>
"nmap <C-H> <C-W>h
"nmap <C-J> <C-W>j
"nmap <C-K> <C-W>k
"nmap <C-K> <C-W>l

"let g:SrcExpl_winHeight = 8
"let g:SrcExpl_refreshTime = 100
"let g:SrcExpl_jumpKey = "<ENTER>"
"let g:SrcExpl_gobackKey = "<SPACE>"
"let g:SrcExpl_isUpdateTags = 0

hi ExtraWhitespace ctermbg=red guibg=red
match ExtraWhitespace /\s\+$\| \+\ze\t/

"autocmd BufReadPost *
"  \ if line("'\"") > 0 && line("'\"") <= line("$") |
"    \   exe "normal g`\"" |
"	  \ endif

"------------------------------------------------------------------
" solarized color
"syntax enable
"set background=dark
"set t_Co=256
"colorscheme solarized
"if has('gui_running')
"    set background=light
"else
"    set background=dark
"endif
"let g:solarized_termcolors=256
"------------------------------------------------------------------
" Seoul256 Color
" Unified color scheme (default: dark)
" colo seoul256

" Light color scheme
" colo seoul256-light

" Switch
" set background=dark
" seoul256 (dark):
"   Range:   233 (darkest) ~ 239 (lightest)
"   Default: 237
" let g:seoul256_background = 233
" let g:seoul256_light_background = 256
"------------------------------------------------------------------
set t_Co=256
colorscheme jellybeans
set background=dark

let g:jellybeans_overrides = {
	\    'Todo': { 'guifg': '303030', 'guibg': 'f0f000',
	\              'ctermfg': 'Black', 'ctermbg': 'Yellow',
	\              'attr': 'bold' },
	\    'Comment': { 'guifg': 'cccccc' },
	\}
let g:jellybeans_overrides = {
	\    'background': { 'guibg': '000000' },
	\}
let g:jellybeans_overrides = {
	\    'background': { 'ctermbg': 'none', '256ctermbg': 'none' },
	\}
let g:jellybeans_use_lowcolor_black = 0
"----------------------------------------------------------------------

" airline
let g:airline#extensions#tabline#enabled = 1 " turn on buffer list
let g:airline_theme='hybrid'
"let g:airline_theme='wombat'
set laststatus=2 " turn on bottom bar

" Smarter tab line 활성화: 모든 파일 버퍼 출력
let g:airline#extensions#tabline#enabled = 1

" Tab line 구분자 '|' 로 설정
let g:airline#extensions#tabline#left_sep = ' '
let g:airline#extensions#tabline#left_alt_sep = '|'

" Tab line 에 파일명만 출력되도록 설정
let g:airline#extensions#tabline#formatter = 'unique_tail'

" Powerline-font 활성화
let g:airline_powerline_fonts = 1 

"let g:promptline_theme = 'jelly'
let g:promptline_theme = 'airline'
let g:promptline_preset = {
      \'a'    : [ '$(hostname)' ],
      \'b'    : [ '$(whoami)' ],
      \'c'    : [ '\w' ],
      \'options': {
          \'left_sections' : [ 'b', 'a' ],
          \'right_sections' : [ 'c' ],
          \'left_only_sections' : [ 'b', 'a', 'c' ]}}

"let g:lightline = {
"      \ 'colorscheme': 'jellybeans',
"      \ }
      
" <YouCompleteMe> {{
"let g:ycm_global_ycm_extra_conf = '~/.vim/plugged/youcompleteme/third_party/ycmd/.ycm_extra_conf.py'
"let g:ycm_confirm_extra_conf = 0
"let g:ycm_key_list_select_completion = ['<C-j>', '<Down>']
"let g:ycm_key_list_previous_completion = ['<C-i>', '<Up>']
"let g:ycm_autoclose_preview_window_after_completion = 1
"let g:ycm_min_num_of_chars_for_completion = 1
"let g:ycm_auto_trigger = 0
"let g:ycm_python_binary_path = '/usr/bin/python3'
"let g:ycm_log_level = 'debug'
"nnoremap <leader>g :YcmCompleter GoTo<CR>
"nnoremap <leader>gg :YcmCompleter GoToImprecise<CR>
"nnoremap <leader>d :YcmCompleter GoToDeclaration<CR>
"nnoremap <leader>t :YcmCompleter GetType<CR>
"nnoremap <leader>p :YcmCompleter GetParent<CR>
" " }}
