<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <link rel="stylesheet" href="/assets/css/basic.css" type="text/css" title="basic" />
    <link rel="stylesheet" href="/assets/css/print.css" type="text/css"media="print" />
    <link rel="alternate stylesheet" href="/assets/css/fall.css" type="text/css"  title="fall" />
    <link rel="alternate stylesheet" href="/assets/css/summer.css" type="text/css"  title="summer"/>
    <link rel="alternate stylesheet" href="/assets/css/spring.css" type="text/css"  title="spring"/>
    <link rel="alternate stylesheet" href="/assets/css/simple.css" type="text/css"  title="simple"/>
    <link rel="shortcut icon" href="/assets/img/fav.ico" type="image/x-icon" />
    <link rel="alternate" type="application/rss+xml" title="Blog at blogger.com" href="http://feeds.feedburner.com/jicknan" />

    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <meta name="robots" content="all" />
    <meta name="author" content="Jick Nan" />
    <meta name="copyright" content="A site of Jick Nan" />

    <title>Design Notes of FreeLAMP.net</title>

    <script type="text/javascript" src="/assets/js/styleswitcher.js"></script>

    <style type="text/css">
	#sidebartop a:visited {
	    font-weight: normal;
	    background: #888;
	    color:#fff;
	    text-decoration: none;
	}
    </style>
</head>

<body>

    <div id="header">
	<span id="logo">Design Notes of FreeLAMP.net</span>
	<span id="mtime">[ <script type="text/javascript" src="/assets/js/datestamp.js"></script> ]</span>
    </div>
<div id="sidebar">
    <hr />
    <ul id="menu">
        <li id="sidebartop"><a href="http://www.freelamp.net/">FreeLAMP.net</a></li>
        <li id="blog"><a href="http://jicknan.blogspot.com/">blog</a></li>
        <li id="photo"><a href="http://photo.freelamp.net">photo</a></li>
    </ul>

    <hr />
    <div id="contrast">
        <ul>
            <li class="first"><a href="#" onclick="setActiveStyleSheet('basic'); return false;">D</a></li>
            <li><a href="#" onclick="setActiveStyleSheet('fall'); return false;">F</a></li>
            <li><a href="#" onclick="setActiveStyleSheet('summer'); return false;">S</a></li>
            <li><a href="#" onclick="setActiveStyleSheet('spring'); return false;">s</a></li></ul></div>

    <hr />
    我在看<br />
    <script type="text/javascript" src="http://www.douban.com/service/badge/jicknan/?show=dolist&select=random&n=3&columns=1&hidelogo=yes" ></script>

    我想看<br />
    <script type="text/javascript" src="http://www.douban.com/service/badge/jicknan/?show=wishlist&select=random&n=3&columns=1&hidelogo=yes" ></script>

    我看过<br />
    <script type="text/javascript" src="http://www.douban.com/service/badge/jicknan/?show=collection&select=random&n=3&columns=1" ></script>

    <hr />
    <!-- Start of Flickr Badge -->
    <style type="text/css">
        #flickr_badge_source_txt {padding:0; font: 11px Arial, Helvetica, Sans serif; color:#666666;}
        #flickr_badge_icon {display:block !important; margin:0 !important; border: 1px solid rgb(0, 0, 0) !important;}
        #flickr_icon_td {padding:0 5px 0 0 !important;}
        .flickr_badge_image {text-align:center !important;}
        .flickr_badge_image img {border: 1px solid black !important;}
        #flickr_badge_uber_wrapper {width:150px;}
        #flickr_www {display:block; text-align:center; padding:0 10px 0 10px !important; font: 11px Arial, Helvetica, Sans serif !important; color:#3993ff !important;}
        #flickr_badge_uber_wrapper a:hover,
        #flickr_badge_uber_wrapper a:link,
        #flickr_badge_uber_wrapper a:active,
        #flickr_badge_uber_wrapper a:visited {text-decoration:none !important; background:inherit !important;color:#3993ff;}
        #flickr_badge_source {padding:0 !important; font: 11px Arial, Helvetica, Sans serif !important; color:#666666 !important;}
    </style>
    <table id="flickr_badge_uber_wrapper" cellpadding="0" cellspacing="10" border="0"><tr><td><a href="http://www.flickr.com" id="flickr_www">www.<strong style="color:#3993ff">flick<span style="color:#ff1c92">r</span></strong>.com</a><table cellpadding="0" cellspacing="10" border="0">
    <script type="text/javascript" src="http://www.flickr.com/badge_code_v2.gne?show_name=1&count=5&display=random&size=s&layout=v&source=user&user=56267554%40N00"></script>
    <tr>
        <td id="flickr_badge_source" valign="center" align="center">
            <table cellpadding="0" cellspacing="0" border="0"><tr>
                    <td id="flickr_badge_source_txt"><nobr>More of</nobr> <a href="http://www.flickr.com/photos/jicknan/">jick nan's photos</a></td>
            </tr></table>
        </td>
    </tr>
</table>
</td></tr></table>
<!-- End of Flickr Badge -->

<hr />
<ul>
    <li>陕ICP备05015297</li>
</ul>

</div>
<div id="content">

    <div id="brave400">

	<h2>设计原则</h2>

	<p>本站设计目的是传递信息，而不是显示各个浏览器的局限性，或者通过图片艺术来打动人。因此，本站的原则如下：</p>

	<ol>
	    <li><dl> <dt>简约而不简单。</dt>
		<dd>简洁、最低限度的代码、风格。</dd></dl></li>

	    <li><dl><dt>Do not reinvent the wheel!</dt>
		<dd>为了不重复建设，本站广泛参考了以下网站：<a href="http://www.catb.org/~esr/" title="Eric S. Raymond&apos;s Personal Home Page">Eric Raymond</a>、<a href="http://www.zeldman.com/" title="Jeffrey Zeldman&acute;s Homepage">Jeffrey Zeldman</a>、<a href="http://www.meyerweb.com/" title="css/edge 最新、最兼容">Eric Meyer</a>。</dd></dl></li>

	    <li><dl><dt>一个文档服务于全部：PC, PDA, WAP, Palm...</dt>
		<dd>FreeLAMP.net 严格采用 XHTML 1.0 建造，采用 CSS 布局排版。本站没有 Palm 版本或 WAP 版本，也不再需要多版本，当你使用标准去设计和建造，一个文档就可以服务全部。</dd></dl></li>

	</ol>

	<h2>标准设计</h2>

	<p>本站采用 <a href="http://www.webstandards.org" title="Web 标准化组织">Web 标准</a>进行设计，遵循 <a href="http://www.w3.org/TR/xhtml1" title="XHTML 1.0 Specification">XHTML 1.0 Strict</a>、<a href="http://www.w3.org/TR/REC-CSS2/" title="CSS level 2 Specification">CSS level 2</a>、<a href="http://www.ecma.ch/ecmal/STAND/ECMA-262.HTM" title="ECMAScript 262 Standard">ECMAScript 262</a>、<a href="http://backend.userland.com/rss" title="Rich Site Summury">RSS2</a>等标准，而不迁就于任何浏览器。因此，如果你在浏览的过程中出现了问题，请首先考虑是否是你的浏览器不支持标准或对标准支持有误的结果。</p>

	<p>在 Web 标准实施的过程中，Jeffrey Zeldman 的<a href="http://zeldman.com/dwws/">《Designing with web standards》</a>（中文版<a href="http://www.csdn.net/WebSiteRefactory/">《网站重构》</a>由傅捷等翻译）是我采用的主要指导书。</p>

	<h2>专项技术</h2>
	<p>在本站的中，运用了许多重要的技术。我在这里把相关的信息整理出来，希望能够给愿意采用这些技术的人以参考。</p>
	<ol>
	    <li><dl><dt>轮换样式表</dt>
		<dd>按照 W3C 的说法，我们应该为用户创建一个可以选择样式的网站。在创建这个网站的过程中，我主要参考了来自 London 的 Paul Sowden 的文章： “<a href="http://blog.chinaunix.net/article.php?articleId=24290&blogId=6640">Alternative Style: Working With Alternate Style Sheets</a>。他在文章中清楚的说明了如何创建和使用可轮换样式表。</dd>
		<dd>本站的目标是创建四个样式表，并且按照四季更替，不过目前还没有完成:-)</dd>
		<dd>同时，也保留了本站的第一个样式表，并命名为 <a href="#" onclick="setActiveStyleSheet('simple'); return false;">Simple</a>。因为比之于后来的样式，这个真的很简洁。</dd></dl></li>

	    <li><dl><dt>打印样式表</dt>
		<dd>为了方便的打印出本站的重要信息，本站专门根据打印的特殊要求，设计了一个<a href="/assets/css/print.css">样式表</a>，称为“打印样式表”。</dd>
		<dd>我主要参考了 Eric Meyer 的两篇文章：一是描述媒介相关（media-specific）样式表基础知识的“<a href="http://blog.chinaunix.net/article.php?articleId=24790&blogId=6640">Print Different</a>”；一篇是描述打印样式表在 ALA 具体实施的 “<a href="http://blog.chinaunix.net/article.php?articleId=24803&blogId=6640">CSS Design: Going to Print</a>"。另外就是 ALA 现在使用的<a href="http://www.alistapart.com/c/print.css">打印样式表</a>。</dd></dl></li>
	</ol>

	<h2>浏览器 BUGS：解决的和未解决的</h2>
	<ol>
	    <li><dl><dt>盒模型(Box Model)及其失效与失效之补救(Box Model Hack)</dt>
		<dd>自从 1996 年 CSS1 推出，W3C 即建议网页上的所有对象都放在一个盒中，设计师可以通过规则来控制这个盒的属性。</dd>
		<dd>但是，具体到浏览器厂商的支持，就产生了差异。盒模型定义请看：<a href="http://www.w3.org/TD/REC-CSS2/box.html">http://www.w3.org/TD/REC-CSS2/box.html</a>；盒模型的失效与补救请看：<a href="http://tantek.com/CSS/Examples/boxmodelhack.html">Box Model Hack</a>。</dd></dl></li>

	    <li><dl><dt>IE/Windows 的浮动模型（float model）Bug</dt>
		<dd>IE6/Windows 的一个程序 Bug 会删减浮动在 div 里的较长文档，使读者看不到完整的文档，同时还会造成滚动条的消失。</dd>
		<dd>“<a href="http://www.onestab.net/a/pie/articles/float-bugs-1.html">IE 浮动模型的 Bug</a>” 一文很好的解释了这一现象。</dd></dl></li>

	    <li><dl><dt>IE/Windows 的空格 Bug</dt>
		<dd>空格 Bug 是 Netscape Navigator 的一个知名问题，其历史可以追溯到 3.0 版本。微软为了与之竞争，仿效了 Netscape 的许多行为，很不幸的也包括一些 Bug。截至到 IE6/Windows，这个空格 Bug 一直都存在着。</dd>
		<dd>解决这个 Bug 的方法很简单，删除代码间的空格，但是这样严重影响了代码的可读性，牺牲太大了；又因为此 Bug 对本站影响不大，所以没有消灭。</dd></dl></li>

	</ol>

	<h2>Todos：未来工作</h2>
	<ol>
	    <li>按照四季的风格写全四个 CSS 样式表，最好能够通过 js 自动轮换。</li>
	    <li>将首页的 Fortune Cookie 做成动态的，使用 js 调用，每月自动轮换。</li>
	    <li>用 PHP 写一个在线代码编辑器，连改一个标点都下载下来编辑，太麻烦了。{已经修改好了一个 OnText，并准备继续完善。}</li>
	</ol>

	<h2>报告 bugs</h2>

	<p>这里有两类 bugs 可能影响你浏览本站。一个问题在于我的 XHTML/CSS/JavaScript；
	另一个问题则源于你的浏览器，包括不兼容 W3C 标准。</p>

	<p>本站永远欢迎报告失效链接。</p>

    </div>

</div>
    <div id="footer">
	<p style="text-align: center;">A site of <a href="http://jick.nan.googlepages.com">Jick nan</a> &lt;jick.nan 在 gmail.com&gt; <a href="http://my.statcounter.com/project/standard/stats.php?project_id=1395096"><img alt="Stat Counter" src="http://c13.statcounter.com/counter.php?sc_project=1395096&amp;java=0&amp;security=ed34e4bb&amp;invisible=0"></a></p> 
	<p style="text-align: center;">&nbsp;Powered by <a href="http://www.freelamp.net">FreeLAMP.net</a> :-) </p> 
	<!--Start of Google Analytics -->
	<script src="http://www.google-analytics.com/urchin.js" type="text/javascript"></script>
	<script type="text/javascript">
	    _uacct = "UA-62255-1";
	    urchinTracker();
	</script>
	<!-- End of Google Analytics -->

    </div>

  </body>
</html>
