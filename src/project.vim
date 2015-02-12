let SessionLoad = 1
if &cp | set nocp | endif
nmap d :cs find d =expand("<cword>")	
nmap i :cs find i ^=expand("<cfile>")$
nmap f :cs find f =expand("<cfile>")	
nmap e :cs find e =expand("<cword>")	
nmap t :cs find t =expand("<cword>")	
nmap c :cs find c =expand("<cword>")	
nmap g :cs find g =expand("<cword>")	
nmap s :cs find s =expand("<cword>")	
nmap ,ha :call InsertHeadDefN()
let s:cpo_save=&cpo
set cpo&vim
nmap gx <Plug>NetrwBrowseX
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
nmap <Nul><Nul>d :vert scs find d =expand("<cword>")
nmap <Nul><Nul>i :vert scs find i ^=expand("<cfile>")$	
nmap <Nul><Nul>f :vert scs find f =expand("<cfile>")	
nmap <Nul><Nul>e :vert scs find e =expand("<cword>")
nmap <Nul><Nul>t :vert scs find t =expand("<cword>")
nmap <Nul><Nul>c :vert scs find c =expand("<cword>")
nmap <Nul><Nul>g :vert scs find g =expand("<cword>")
nmap <Nul><Nul>s :vert scs find s =expand("<cword>")
nmap <Nul>d :scs find d =expand("<cword>")	
nmap <Nul>i :scs find i ^=expand("<cfile>")$	
nmap <Nul>f :scs find f =expand("<cfile>")	
nmap <Nul>e :scs find e =expand("<cword>")	
nmap <Nul>t :scs find t =expand("<cword>")	
nmap <Nul>c :scs find c =expand("<cword>")	
nmap <Nul>g :scs find g =expand("<cword>")	
nmap <Nul>s :scs find s =expand("<cword>")	
let &cpo=s:cpo_save
unlet s:cpo_save
set backspace=indent,eol,start
set cscopeprg=/usr/bin/cscope
set cscopetag
set cscopeverbose
set fileencodings=ucs-bom,utf-8,latin1
set formatoptions=tcql
set guicursor=n-v-c:block,o:hor50,i-ci:hor15,r-cr:hor30,sm:block,a:blinkon0
set helplang=en
set history=50
set hlsearch
set mouse=a
set ruler
set shiftwidth=2
set viminfo='20,\"50
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/git/TransSystem/src
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +126 trans/TransTask.h
badd +65 trans/TaskContext.h
badd +106 trans/TransExecQueue.cpp
silent! argdel *
edit trans/TransExecQueue.cpp
set splitbelow splitright
set nosplitbelow
set nosplitright
wincmd t
set winheight=1 winwidth=1
argglobal
let s:cpo_save=&cpo
set cpo&vim
inoremap <buffer> <S-F9> :CCmdlineArgs 
inoremap <buffer> <silent> <C-F9> :call C_Run()
inoremap <buffer> <silent> <F9> :call C_Link():call C_HlMessage()
inoremap <buffer> <silent> <M-F9> :call C_Compile():call C_HlMessage()
nnoremap <buffer> <silent> <NL> i=C_JumpCtrlJ()
vnoremap <buffer> /* s/*  */<Left><Left><Left>p
inoremap <buffer> <silent> ­ =EchoFuncP()
inoremap <buffer> <silent> ½ =EchoFuncN()
vnoremap <buffer> <silent> \rh :call C_Hardcopy()
vnoremap <buffer> <silent> \nm :call C_ProtoPick("method")
vnoremap <buffer> <silent> \nf :call C_ProtoPick("function")
vnoremap <buffer> <silent> \np :call C_ProtoPick("function")
vnoremap <buffer> <silent> \nw :call C_CodeSnippet("wv")
vnoremap <buffer> <silent> \in :call C_CodeFor("down","v")
vnoremap <buffer> <silent> \i0 :call C_CodeFor("up","v")
vnoremap <buffer> <silent> \pi0 :call C_PPIf0("v")
vnoremap <buffer> <silent> \cx :call C_CommentToggle( )
vnoremap <buffer> <silent> \cn :call C_NonCCommentToggle( )
vnoremap <buffer> <silent> \co :call C_CommentToCode():nohlsearch
vnoremap <buffer> <silent> \cc :call C_CodeToCommentCpp():nohlsearchj
vnoremap <buffer> <silent> \c* :call C_CodeToCommentC():nohlsearchj
vnoremap <buffer> <silent> \hd :call mmtemplates#core#InsertTemplate(g:C_Templates,"Help.doxygen cmd")
nnoremap <buffer> <silent> \hd :call mmtemplates#core#InsertTemplate(g:C_Templates,"Help.doxygen cmd")
vnoremap <buffer> <silent> \he :call mmtemplates#core#InsertTemplate(g:C_Templates,"Help.english")
nnoremap <buffer> <silent> \he :call mmtemplates#core#InsertTemplate(g:C_Templates,"Help.english")
vnoremap <buffer> <silent> \+rt :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.RTTI","v")
nnoremap <buffer> <silent> \+rt :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.RTTI")
vnoremap <buffer> <silent> \+na :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.namespace alias")
nnoremap <buffer> <silent> \+na :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.namespace alias")
vnoremap <buffer> <silent> \+unb :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.namespace block xxx","v")
nnoremap <buffer> <silent> \+unb :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.namespace block xxx")
vnoremap <buffer> <silent> \+un :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.using namespace xxx")
nnoremap <buffer> <silent> \+un :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.using namespace xxx")
vnoremap <buffer> <silent> \+uns :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.using namespace std")
nnoremap <buffer> <silent> \+uns :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.using namespace std")
vnoremap <buffer> <silent> \+oof :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.open output file","v")
nnoremap <buffer> <silent> \+oof :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.open output file")
vnoremap <buffer> <silent> \+oif :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.open input file","v")
nnoremap <buffer> <silent> \+oif :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.open input file")
vnoremap <buffer> <silent> \+ex :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.extern C","v")
nnoremap <buffer> <silent> \+ex :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.extern C")
vnoremap <buffer> <silent> \+caa :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.catch all","v")
nnoremap <buffer> <silent> \+caa :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.catch all")
vnoremap <buffer> <silent> \+ca :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.catch","v")
nnoremap <buffer> <silent> \+ca :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.catch")
vnoremap <buffer> <silent> \+tr :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.try catch","v")
nnoremap <buffer> <silent> \+tr :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.try catch")
vnoremap <buffer> <silent> \+ioi :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.operator, in")
nnoremap <buffer> <silent> \+ioi :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.operator, in")
vnoremap <buffer> <silent> \+ioo :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.operator, out")
nnoremap <buffer> <silent> \+ioo :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.operator, out")
vnoremap <buffer> <silent> \+tf :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.template function")
nnoremap <buffer> <silent> \+tf :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.template function")
vnoremap <buffer> <silent> \+ita :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.template accessor")
nnoremap <buffer> <silent> \+ita :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.template accessor")
vnoremap <buffer> <silent> \+itm :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.template method")
nnoremap <buffer> <silent> \+itm :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.template method")
vnoremap <buffer> <silent> \+itcn :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.template class using new")
nnoremap <buffer> <silent> \+itcn :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.template class using new")
vnoremap <buffer> <silent> \+itc :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.template class")
nnoremap <buffer> <silent> \+itc :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.template class")
vnoremap <buffer> <silent> \+ia :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.accessor")
nnoremap <buffer> <silent> \+ia :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.accessor")
vnoremap <buffer> <silent> \+im :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.method")
nnoremap <buffer> <silent> \+im :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.method")
vnoremap <buffer> <silent> \+icn :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.class using new")
nnoremap <buffer> <silent> \+icn :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.class using new")
vnoremap <buffer> <silent> \+ic :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.class")
nnoremap <buffer> <silent> \+ic :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.class")
vnoremap <buffer> <silent> \+ec :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.error class")
nnoremap <buffer> <silent> \+ec :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.error class")
vnoremap <buffer> <silent> \+tcn :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.template class using new")
nnoremap <buffer> <silent> \+tcn :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.template class using new")
vnoremap <buffer> <silent> \+tc :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.template class")
nnoremap <buffer> <silent> \+tc :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.template class")
vnoremap <buffer> <silent> \+cn :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.class using new")
nnoremap <buffer> <silent> \+cn :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.class using new")
vnoremap <buffer> <silent> \+c :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.class")
nnoremap <buffer> <silent> \+c :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.class")
vnoremap <buffer> <silent> \+fb :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.ios flagbits")
nnoremap <buffer> <silent> \+fb :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.ios flagbits")
vnoremap <buffer> <silent> \+om :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.output manipulators")
nnoremap <buffer> <silent> \+om :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.output manipulators")
vnoremap <buffer> <silent> \+ich :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.include C std lib header")
nnoremap <buffer> <silent> \+ich :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.include C std lib header")
vnoremap <buffer> <silent> \+ih :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.include C++ std lib header")
nnoremap <buffer> <silent> \+ih :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.include C++ std lib header")
vnoremap <buffer> <silent> \pw :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.warning")
nnoremap <buffer> <silent> \pw :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.warning")
vnoremap <buffer> <silent> \pp :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.pragma")
nnoremap <buffer> <silent> \pp :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.pragma")
vnoremap <buffer> <silent> \pli :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.line")
nnoremap <buffer> <silent> \pli :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.line")
vnoremap <buffer> <silent> \pe :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.error")
nnoremap <buffer> <silent> \pe :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.error")
vnoremap <buffer> <silent> \pind :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.ifndef-def-endif","v")
nnoremap <buffer> <silent> \pind :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.ifndef-def-endif")
vnoremap <buffer> <silent> \pin :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.ifndef-else-endif","v")
nnoremap <buffer> <silent> \pin :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.ifndef-else-endif")
vnoremap <buffer> <silent> \pid :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.ifdef-else-endif","v")
nnoremap <buffer> <silent> \pid :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.ifdef-else-endif")
vnoremap <buffer> <silent> \pie :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.if-else-endif","v")
nnoremap <buffer> <silent> \pie :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.if-else-endif")
vnoremap <buffer> <silent> \pif :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.if-endif","v")
nnoremap <buffer> <silent> \pif :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.if-endif")
vnoremap <buffer> <silent> \pu :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.undefine")
nnoremap <buffer> <silent> \pu :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.undefine")
vnoremap <buffer> <silent> \pd :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.define")
nnoremap <buffer> <silent> \pd :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.define")
vnoremap <buffer> <silent> \pl :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.include-local")
nnoremap <buffer> <silent> \pl :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.include-local")
vnoremap <buffer> <silent> \pg :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.include-global")
nnoremap <buffer> <silent> \pg :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.include-global")
vnoremap <buffer> <silent> \pih :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.include std lib header")
nnoremap <buffer> <silent> \pih :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.include std lib header")
vnoremap <buffer> <silent> \ifsc :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.fscanf")
nnoremap <buffer> <silent> \ifsc :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.fscanf")
vnoremap <buffer> <silent> \ifpr :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.fprintf")
nnoremap <buffer> <silent> \ifpr :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.fprintf")
vnoremap <buffer> <silent> \io :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.open-output-file","v")
nnoremap <buffer> <silent> \io :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.open-output-file")
vnoremap <buffer> <silent> \ii :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.open-input-file","v")
nnoremap <buffer> <silent> \ii :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.open-input-file")
vnoremap <buffer> <silent> \ias :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.assert","v")
nnoremap <buffer> <silent> \ias :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.assert")
vnoremap <buffer> <silent> \isi :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.sizeof","v")
nnoremap <buffer> <silent> \isi :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.sizeof")
vnoremap <buffer> <silent> \ire :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.realloc")
nnoremap <buffer> <silent> \ire :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.realloc")
vnoremap <buffer> <silent> \ima :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.malloc")
nnoremap <buffer> <silent> \ima :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.malloc")
vnoremap <buffer> <silent> \ica :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.calloc")
nnoremap <buffer> <silent> \ica :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.calloc")
vnoremap <buffer> <silent> \ipr :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.printf")
nnoremap <buffer> <silent> \ipr :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.printf")
vnoremap <buffer> <silent> \isc :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.scanf")
nnoremap <buffer> <silent> \isc :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.scanf")
vnoremap <buffer> <silent> \iu :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.union","v")
nnoremap <buffer> <silent> \iu :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.union")
vnoremap <buffer> <silent> \is :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.struct","v")
nnoremap <buffer> <silent> \is :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.struct")
vnoremap <buffer> <silent> \ie :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.enum","v")
nnoremap <buffer> <silent> \ie :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.enum")
vnoremap <buffer> <silent> \im :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.main","v")
nnoremap <buffer> <silent> \im :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.main")
vnoremap <buffer> <silent> \isf :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.function-static","v")
nnoremap <buffer> <silent> \isf :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.function-static")
vnoremap <buffer> <silent> \if :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.function","v")
nnoremap <buffer> <silent> \if :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.function")
vnoremap <buffer> <silent> \sb :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.block","v")
nnoremap <buffer> <silent> \sb :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.block")
vnoremap <buffer> <silent> \sc :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.case")
nnoremap <buffer> <silent> \sc :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.case")
vnoremap <buffer> <silent> \ss :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.switch","v")
nnoremap <buffer> <silent> \ss :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.switch")
vnoremap <buffer> <silent> \swh :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.while block","v")
nnoremap <buffer> <silent> \swh :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.while block")
vnoremap <buffer> <silent> \sw :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.while")
nnoremap <buffer> <silent> \sw :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.while")
vnoremap <buffer> <silent> \se :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.else block","v")
nnoremap <buffer> <silent> \se :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.else block")
vnoremap <buffer> <silent> \sife :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.if block else","v")
nnoremap <buffer> <silent> \sife :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.if block else")
vnoremap <buffer> <silent> \sie :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.if else","v")
nnoremap <buffer> <silent> \sie :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.if else")
vnoremap <buffer> <silent> \sif :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.if block","v")
nnoremap <buffer> <silent> \sif :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.if block")
vnoremap <buffer> <silent> \si :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.if")
nnoremap <buffer> <silent> \si :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.if")
vnoremap <buffer> <silent> \sfr :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.range-based for","v")
nnoremap <buffer> <silent> \sfr :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.range-based for")
vnoremap <buffer> <silent> \sfo :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.for block","v")
nnoremap <buffer> <silent> \sfo :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.for block")
vnoremap <buffer> <silent> \sf :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.for")
nnoremap <buffer> <silent> \sf :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.for")
vnoremap <buffer> <silent> \sd :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.do while","v")
nnoremap <buffer> <silent> \sd :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.do while")
vnoremap <buffer> <silent> \ct :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.date time")
nnoremap <buffer> <silent> \ct :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.date time")
vnoremap <buffer> <silent> \cd :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.date")
nnoremap <buffer> <silent> \cd :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.date")
vnoremap <buffer> <silent> \cma :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.macros")
nnoremap <buffer> <silent> \cma :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.macros")
vnoremap <buffer> <silent> \csc :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.special comments")
nnoremap <buffer> <silent> \csc :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.special comments")
vnoremap <buffer> <silent> \ckc :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.keyword comments")
nnoremap <buffer> <silent> \ckc :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.keyword comments")
vnoremap <buffer> <silent> \chs :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.H file sections")
nnoremap <buffer> <silent> \chs :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.H file sections")
vnoremap <buffer> <silent> \ccs :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.C file sections")
nnoremap <buffer> <silent> \ccs :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.C file sections")
vnoremap <buffer> <silent> \cfdh :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.file description header")
nnoremap <buffer> <silent> \cfdh :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.file description header")
vnoremap <buffer> <silent> \cfdi :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.file description impl")
nnoremap <buffer> <silent> \cfdi :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.file description impl")
vnoremap <buffer> <silent> \ccl :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.class")
nnoremap <buffer> <silent> \ccl :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.class")
vnoremap <buffer> <silent> \cme :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.method")
nnoremap <buffer> <silent> \cme :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.method")
vnoremap <buffer> <silent> \cfu :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.function")
nnoremap <buffer> <silent> \cfu :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.function")
vnoremap <buffer> <silent> \cfr :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.frame")
nnoremap <buffer> <silent> \cfr :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.frame")
vnoremap <buffer> <silent> \njt :call mmtemplates#core#InsertTemplate(g:C_Templates,"Snippets.jump tags")
nnoremap <buffer> <silent> \njt :call mmtemplates#core#InsertTemplate(g:C_Templates,"Snippets.jump tags")
noremap <buffer> <silent> \hm :call C_Help("m")
noremap <buffer> <silent> \hp :call C_HelpCsupport()
noremap <buffer> <silent> \ro :call C_Toggle_Gvim_Xterm()
noremap <buffer> <silent> \rx :call C_XtermSize()
noremap <buffer> <silent> \rs :call C_Settings()
nnoremap <buffer> <silent> \rh :call C_Hardcopy()
onoremap <buffer> <silent> \rh :call C_Hardcopy()
noremap <buffer> <silent> \ri :call C_Indent()
noremap <buffer> <silent> \rccs :call C_CppcheckSeverityInput()
noremap <buffer> <silent> \rcc :call C_CppcheckCheck():call C_HlMessage()
noremap <buffer> <silent> \rpa :call C_SplintArguments()
noremap <buffer> <silent> \rp :call C_SplintCheck():call C_HlMessage()
noremap <buffer> <silent> \rd :call C_Debugger()
noremap <buffer> \ra :CCmdlineArgs 
noremap <buffer> <silent> \re :call C_ExeToRun()
noremap <buffer> <silent> \rr :call C_Run()
noremap <buffer> <silent> \rl :call C_Link():call C_HlMessage()
noremap <buffer> <silent> \rc :call C_Compile():call C_HlMessage()
nnoremap <buffer> <silent> \nts :call mmtemplates#core#ChooseStyle(g:C_Templates,"!pick")
nnoremap <buffer> <silent> \ntr :call mmtemplates#core#ReadTemplates(g:C_Templates,"reload","all")
nnoremap <buffer> <silent> \ntl :call mmtemplates#core#EditTemplateFiles(g:C_Templates,-1)
noremap <buffer> <silent> \ns :call C_ProtoShow()
noremap <buffer> <silent> \nc :call C_ProtoClear()
noremap <buffer> <silent> \ni :call C_ProtoInsert()
nnoremap <buffer> <silent> \nm :call C_ProtoPick("method")
onoremap <buffer> <silent> \nm :call C_ProtoPick("method")
nnoremap <buffer> <silent> \nf :call C_ProtoPick("function")
onoremap <buffer> <silent> \nf :call C_ProtoPick("function")
nnoremap <buffer> <silent> \np :call C_ProtoPick("function")
onoremap <buffer> <silent> \np :call C_ProtoPick("function")
noremap <buffer> <silent> \ne :call C_CodeSnippet("e")
nnoremap <buffer> <silent> \nw :call C_CodeSnippet("w")
onoremap <buffer> <silent> \nw :call C_CodeSnippet("w")
noremap <buffer> <silent> \nv :call C_CodeSnippet("view")
noremap <buffer> <silent> \nr :call C_CodeSnippet("r")
nnoremap <buffer> <silent> \in :call C_CodeFor("down"    )
onoremap <buffer> <silent> \in :call C_CodeFor("down"    )
nnoremap <buffer> <silent> \i0 :call C_CodeFor("up"    )
onoremap <buffer> <silent> \i0 :call C_CodeFor("up"    )
noremap <buffer> <silent> \pr0 :call C_PPIf0Remove()
nnoremap <buffer> <silent> \pi0 :call C_PPIf0("a")2ji
onoremap <buffer> <silent> \pi0 :call C_PPIf0("a")2ji
nnoremap <buffer> <silent> \cx :call C_CommentToggle( )
onoremap <buffer> <silent> \cx :call C_CommentToggle( )
nnoremap <buffer> <silent> \cn :call C_NonCCommentToggle( )
onoremap <buffer> <silent> \cn :call C_NonCCommentToggle( )
nnoremap <buffer> <silent> \co :call C_CommentToCode():nohlsearch
onoremap <buffer> <silent> \co :call C_CommentToCode():nohlsearch
nnoremap <buffer> <silent> \cc :call C_CodeToCommentCpp():nohlsearchj
onoremap <buffer> <silent> \cc :call C_CodeToCommentCpp():nohlsearchj
nnoremap <buffer> <silent> \c* :call C_CodeToCommentC():nohlsearchj
onoremap <buffer> <silent> \c* :call C_CodeToCommentC():nohlsearchj
noremap <buffer> <silent> \cs :call C_GetLineEndCommCol()
vnoremap <buffer> <silent> \cj :call C_AdjustLineEndComm()
nnoremap <buffer> <silent> \cj :call C_AdjustLineEndComm()
noremap <buffer> <silent> \cl :call C_EndOfLineComment()
noremap <buffer> \rcm :MakeFile 
noremap <buffer> \rma :MakeCmdlineArgs 
noremap <buffer> <silent> \rmc :Make clean
noremap <buffer> <silent> \rm :Make
vnoremap <buffer> { S{}Pk=iB
noremap <buffer> <S-F9> :CCmdlineArgs 
noremap <buffer> <silent> <C-F9> :call C_Run()
noremap <buffer> <silent> <F9> :call C_Link():call C_HlMessage()
noremap <buffer> <silent> <M-F9> :call C_Compile():call C_HlMessage()
inoremap <buffer> <silent> <NL> =C_JumpCtrlJ()
inoremap <buffer> <silent> ( (=EchoFunc()
inoremap <buffer> <silent> ) =EchoFuncClear())
inoremap <buffer> /* /*/kA 
inoremap <buffer> /* /*  */<Left><Left><Left>
inoremap <buffer> <silent> \hd :call mmtemplates#core#InsertTemplate(g:C_Templates,"Help.doxygen cmd","i")
inoremap <buffer> <silent> \he :call mmtemplates#core#InsertTemplate(g:C_Templates,"Help.english","i")
inoremap <buffer> <silent> \+rt :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.RTTI","i")
inoremap <buffer> <silent> \+na :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.namespace alias","i")
inoremap <buffer> <silent> \+unb :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.namespace block xxx","i")
inoremap <buffer> <silent> \+un :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.using namespace xxx","i")
inoremap <buffer> <silent> \+uns :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.using namespace std","i")
inoremap <buffer> <silent> \+oof :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.open output file","i")
inoremap <buffer> <silent> \+oif :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.open input file","i")
inoremap <buffer> <silent> \+ex :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.extern C","i")
inoremap <buffer> <silent> \+caa :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.catch all","i")
inoremap <buffer> <silent> \+ca :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.catch","i")
inoremap <buffer> <silent> \+tr :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.try catch","i")
inoremap <buffer> <silent> \+ioi :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.operator, in","i")
inoremap <buffer> <silent> \+ioo :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.operator, out","i")
inoremap <buffer> <silent> \+tf :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.template function","i")
inoremap <buffer> <silent> \+ita :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.template accessor","i")
inoremap <buffer> <silent> \+itm :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.template method","i")
inoremap <buffer> <silent> \+itcn :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.template class using new","i")
inoremap <buffer> <silent> \+itc :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.template class","i")
inoremap <buffer> <silent> \+ia :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.accessor","i")
inoremap <buffer> <silent> \+im :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.method","i")
inoremap <buffer> <silent> \+icn :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.class using new","i")
inoremap <buffer> <silent> \+ic :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.IMPLEMENTATION.class","i")
inoremap <buffer> <silent> \+ec :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.error class","i")
inoremap <buffer> <silent> \+tcn :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.template class using new","i")
inoremap <buffer> <silent> \+tc :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.template class","i")
inoremap <buffer> <silent> \+cn :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.class using new","i")
inoremap <buffer> <silent> \+c :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.class","i")
inoremap <buffer> <silent> \+fb :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.ios flagbits","i")
inoremap <buffer> <silent> \+om :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.output manipulators","i")
inoremap <buffer> <silent> \+ich :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.include C std lib header","i")
inoremap <buffer> <silent> \+ih :call mmtemplates#core#InsertTemplate(g:C_Templates,"C++.include C++ std lib header","i")
inoremap <buffer> <silent> \pw :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.warning","i")
inoremap <buffer> <silent> \pp :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.pragma","i")
inoremap <buffer> <silent> \pli :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.line","i")
inoremap <buffer> <silent> \pe :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.error","i")
inoremap <buffer> <silent> \pind :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.ifndef-def-endif","i")
inoremap <buffer> <silent> \pin :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.ifndef-else-endif","i")
inoremap <buffer> <silent> \pid :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.ifdef-else-endif","i")
inoremap <buffer> <silent> \pie :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.if-else-endif","i")
inoremap <buffer> <silent> \pif :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.if-endif","i")
inoremap <buffer> <silent> \pu :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.undefine","i")
inoremap <buffer> <silent> \pd :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.define","i")
inoremap <buffer> <silent> \pl :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.include-local","i")
inoremap <buffer> <silent> \pg :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.include-global","i")
inoremap <buffer> <silent> \pih :call mmtemplates#core#InsertTemplate(g:C_Templates,"Preprocessor.include std lib header","i")
inoremap <buffer> <silent> \ifsc :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.fscanf","i")
inoremap <buffer> <silent> \ifpr :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.fprintf","i")
inoremap <buffer> <silent> \io :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.open-output-file","i")
inoremap <buffer> <silent> \ii :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.open-input-file","i")
inoremap <buffer> <silent> \ias :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.assert","i")
inoremap <buffer> <silent> \isi :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.sizeof","i")
inoremap <buffer> <silent> \ire :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.realloc","i")
inoremap <buffer> <silent> \ima :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.malloc","i")
inoremap <buffer> <silent> \ica :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.calloc","i")
inoremap <buffer> <silent> \ipr :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.printf","i")
inoremap <buffer> <silent> \isc :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.scanf","i")
inoremap <buffer> <silent> \iu :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.union","i")
inoremap <buffer> <silent> \is :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.struct","i")
inoremap <buffer> <silent> \ie :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.enum","i")
inoremap <buffer> <silent> \im :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.main","i")
inoremap <buffer> <silent> \isf :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.function-static","i")
inoremap <buffer> <silent> \if :call mmtemplates#core#InsertTemplate(g:C_Templates,"Idioms.function","i")
inoremap <buffer> <silent> \sb :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.block","i")
inoremap <buffer> <silent> \sc :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.case","i")
inoremap <buffer> <silent> \ss :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.switch","i")
inoremap <buffer> <silent> \swh :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.while block","i")
inoremap <buffer> <silent> \sw :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.while","i")
inoremap <buffer> <silent> \se :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.else block","i")
inoremap <buffer> <silent> \sife :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.if block else","i")
inoremap <buffer> <silent> \sie :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.if else","i")
inoremap <buffer> <silent> \sif :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.if block","i")
inoremap <buffer> <silent> \si :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.if","i")
inoremap <buffer> <silent> \sfr :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.range-based for","i")
inoremap <buffer> <silent> \sfo :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.for block","i")
inoremap <buffer> <silent> \sf :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.for","i")
inoremap <buffer> <silent> \sd :call mmtemplates#core#InsertTemplate(g:C_Templates,"Statements.do while","i")
inoremap <buffer> <silent> \ct :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.date time","i")
inoremap <buffer> <silent> \cd :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.date","i")
inoremap <buffer> <silent> \cma :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.macros","i")
inoremap <buffer> <silent> \csc :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.special comments","i")
inoremap <buffer> <silent> \ckc :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.keyword comments","i")
inoremap <buffer> <silent> \chs :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.H file sections","i")
inoremap <buffer> <silent> \ccs :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.C file sections","i")
inoremap <buffer> <silent> \cfdh :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.file description header","i")
inoremap <buffer> <silent> \cfdi :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.file description impl","i")
inoremap <buffer> <silent> \ccl :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.class","i")
inoremap <buffer> <silent> \cme :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.method","i")
inoremap <buffer> <silent> \cfu :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.function","i")
inoremap <buffer> <silent> \cfr :call mmtemplates#core#InsertTemplate(g:C_Templates,"Comments.frame","i")
inoremap <buffer> <silent> \njt :call mmtemplates#core#InsertTemplate(g:C_Templates,"Snippets.jump tags","i")
inoremap <buffer> <silent> \hm :call C_Help("m")
inoremap <buffer> <silent> \hp :call C_HelpCsupport()
inoremap <buffer> <silent> \ro :call C_Toggle_Gvim_Xterm()
inoremap <buffer> <silent> \rx :call C_XtermSize()
inoremap <buffer> <silent> \rs :call C_Settings()
inoremap <buffer> <silent> \rh :call C_Hardcopy()
inoremap <buffer> <silent> \ri :call C_Indent()
inoremap <buffer> <silent> \rccs :call C_CppcheckSeverityInput()
inoremap <buffer> <silent> \rcc :call C_CppcheckCheck():call C_HlMessage()
inoremap <buffer> <silent> \rpa :call C_SplintArguments()
inoremap <buffer> <silent> \rp :call C_SplintCheck():call C_HlMessage()
inoremap <buffer> <silent> \rd :call C_Debugger()
inoremap <buffer> \ra :CCmdlineArgs 
inoremap <buffer> <silent> \re :call C_ExeToRun()
inoremap <buffer> <silent> \rr :call C_Run()
inoremap <buffer> <silent> \rl :call C_Link():call C_HlMessage()
inoremap <buffer> <silent> \rc :call C_Compile():call C_HlMessage()
inoremap <buffer> <silent> \nts :call mmtemplates#core#ChooseStyle(g:C_Templates,"!pick")
inoremap <buffer> <silent> \ntr :call mmtemplates#core#ReadTemplates(g:C_Templates,"reload","all")
inoremap <buffer> <silent> \ntl :call mmtemplates#core#EditTemplateFiles(g:C_Templates,-1)
inoremap <buffer> <silent> \ns :call C_ProtoShow()
inoremap <buffer> <silent> \nc :call C_ProtoClear()
inoremap <buffer> <silent> \ni :call C_ProtoInsert()
inoremap <buffer> <silent> \nm :call C_ProtoPick("method")
inoremap <buffer> <silent> \nf :call C_ProtoPick("function")
inoremap <buffer> <silent> \np :call C_ProtoPick("function")
inoremap <buffer> <silent> \ne :call C_CodeSnippet("e")
inoremap <buffer> <silent> \nw :call C_CodeSnippet("w")
inoremap <buffer> <silent> \nv :call C_CodeSnippet("view")
inoremap <buffer> <silent> \nr :call C_CodeSnippet("r")
inoremap <buffer> <silent> \in :call C_CodeFor("down"    )
inoremap <buffer> <silent> \i0 :call C_CodeFor("up"    )
inoremap <buffer> <silent> \pr0 :call C_PPIf0Remove()
inoremap <buffer> <silent> \pi0 :call C_PPIf0("a")2ji
inoremap <buffer> <silent> \cx :call C_CommentToggle( )
inoremap <buffer> <silent> \cn :call C_NonCCommentToggle( )
inoremap <buffer> <silent> \co :call C_CommentToCode():nohlsearch
inoremap <buffer> <silent> \cc :call C_CodeToCommentCpp():nohlsearchj
inoremap <buffer> <silent> \c* :call C_CodeToCommentC():nohlsearchj
inoremap <buffer> <silent> \cj :call C_AdjustLineEndComm()a
inoremap <buffer> <silent> \cl :call C_EndOfLineComment()
inoremap <buffer> \rcm :MakeFile 
inoremap <buffer> \rma :MakeCmdlineArgs 
inoremap <buffer> <silent> \rmc :Make clean
inoremap <buffer> <silent> \rm :Make
inoremap <buffer> { {}O
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal noautoindent
setlocal nobinary
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal completefunc=
setlocal nocopyindent
setlocal nocursorcolumn
setlocal nocursorline
setlocal define=
setlocal dictionary=~/.vim/c-support/wordlists/c-c++-keywords.list,~/.vim/c-support/wordlists/k+r.list,~/.vim/c-support/wordlists/stl_index.list
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal noexpandtab
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=0
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal nolist
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal modeline
setlocal modifiable
setlocal nrformats=octal,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=2
setlocal noshortname
setlocal nosmartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=8
setlocal tags=
setlocal textwidth=0
setlocal thesaurus=
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal wrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 118 - ((50 * winheight(0) + 28) / 56)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
118
normal! 0
tabnext 1
if exists('s:wipebuf')
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
