(function(){const e=document.createElement("link").relList;if(e&&e.supports&&e.supports("modulepreload"))return;for(const r of document.querySelectorAll('link[rel="modulepreload"]'))o(r);new MutationObserver(r=>{for(const l of r)if(l.type==="childList")for(const d of l.addedNodes)d.tagName==="LINK"&&d.rel==="modulepreload"&&o(d)}).observe(document,{childList:!0,subtree:!0});function n(r){const l={};return r.integrity&&(l.integrity=r.integrity),r.referrerPolicy&&(l.referrerPolicy=r.referrerPolicy),r.crossOrigin==="use-credentials"?l.credentials="include":r.crossOrigin==="anonymous"?l.credentials="omit":l.credentials="same-origin",l}function o(r){if(r.ep)return;r.ep=!0;const l=n(r);fetch(r.href,l)}})();var B,v,he,T,ne,pe,q,Y,J,K,$={},me=[],Ae=/acit|ex(?:s|g|n|p|$)|rph|grid|ows|mnc|ntw|ine[ch]|zoo|^ord|itera/i,Q=Array.isArray;function S(t,e){for(var n in e)t[n]=e[n];return t}function ve(t){t&&t.parentNode&&t.parentNode.removeChild(t)}function Pe(t,e,n){var o,r,l,d={};for(l in e)l=="key"?o=e[l]:l=="ref"?r=e[l]:d[l]=e[l];if(arguments.length>2&&(d.children=arguments.length>3?B.call(arguments,2):n),typeof t=="function"&&t.defaultProps!=null)for(l in t.defaultProps)d[l]===void 0&&(d[l]=t.defaultProps[l]);return j(t,d,o,r,null)}function j(t,e,n,o,r){var l={type:t,props:e,key:n,ref:o,__k:null,__:null,__b:0,__e:null,__d:void 0,__c:null,constructor:void 0,__v:r??++he,__i:-1,__u:0};return r==null&&v.vnode!=null&&v.vnode(l),l}function E(t){return t.children}function F(t,e){this.props=t,this.context=e}function A(t,e){if(e==null)return t.__?A(t.__,t.__i+1):null;for(var n;e<t.__k.length;e++)if((n=t.__k[e])!=null&&n.__e!=null)return n.__e;return typeof t.type=="function"?A(t):null}function ge(t){var e,n;if((t=t.__)!=null&&t.__c!=null){for(t.__e=t.__c.base=null,e=0;e<t.__k.length;e++)if((n=t.__k[e])!=null&&n.__e!=null){t.__e=t.__c.base=n.__e;break}return ge(t)}}function oe(t){(!t.__d&&(t.__d=!0)&&T.push(t)&&!U.__r++||ne!==v.debounceRendering)&&((ne=v.debounceRendering)||pe)(U)}function U(){var t,e,n,o,r,l,d,a;for(T.sort(q);t=T.shift();)t.__d&&(e=T.length,o=void 0,l=(r=(n=t).__v).__e,d=[],a=[],n.__P&&((o=S({},r)).__v=r.__v+1,v.vnode&&v.vnode(o),X(n.__P,o,r,n.__n,n.__P.namespaceURI,32&r.__u?[l]:null,d,l??A(r),!!(32&r.__u),a),o.__v=r.__v,o.__.__k[o.__i]=o,we(d,o,a),o.__e!=l&&ge(o)),T.length>e&&T.sort(q));U.__r=0}function ye(t,e,n,o,r,l,d,a,c,s,p){var _,f,u,h,m,x=o&&o.__k||me,g=e.length;for(n.__d=c,Me(n,e,x),c=n.__d,_=0;_<g;_++)(u=n.__k[_])!=null&&(f=u.__i===-1?$:x[u.__i]||$,u.__i=_,X(t,u,f,r,l,d,a,c,s,p),h=u.__e,u.ref&&f.ref!=u.ref&&(f.ref&&Z(f.ref,null,u),p.push(u.ref,u.__c||h,u)),m==null&&h!=null&&(m=h),65536&u.__u||f.__k===u.__k?c=be(u,c,t):typeof u.type=="function"&&u.__d!==void 0?c=u.__d:h&&(c=h.nextSibling),u.__d=void 0,u.__u&=-196609);n.__d=c,n.__e=m}function Me(t,e,n){var o,r,l,d,a,c=e.length,s=n.length,p=s,_=0;for(t.__k=[],o=0;o<c;o++)(r=e[o])!=null&&typeof r!="boolean"&&typeof r!="function"?(d=o+_,(r=t.__k[o]=typeof r=="string"||typeof r=="number"||typeof r=="bigint"||r.constructor==String?j(null,r,null,null,null):Q(r)?j(E,{children:r},null,null,null):r.constructor===void 0&&r.__b>0?j(r.type,r.props,r.key,r.ref?r.ref:null,r.__v):r).__=t,r.__b=t.__b+1,l=null,(a=r.__i=$e(r,n,d,p))!==-1&&(p--,(l=n[a])&&(l.__u|=131072)),l==null||l.__v===null?(a==-1&&_--,typeof r.type!="function"&&(r.__u|=65536)):a!==d&&(a==d-1?_--:a==d+1?_++:(a>d?_--:_++,r.__u|=65536))):r=t.__k[o]=null;if(p)for(o=0;o<s;o++)(l=n[o])!=null&&!(131072&l.__u)&&(l.__e==t.__d&&(t.__d=A(l)),xe(l,l))}function be(t,e,n){var o,r;if(typeof t.type=="function"){for(o=t.__k,r=0;o&&r<o.length;r++)o[r]&&(o[r].__=t,e=be(o[r],e,n));return e}t.__e!=e&&(e&&t.type&&!n.contains(e)&&(e=A(t)),n.insertBefore(t.__e,e||null),e=t.__e);do e=e&&e.nextSibling;while(e!=null&&e.nodeType===8);return e}function $e(t,e,n,o){var r=t.key,l=t.type,d=n-1,a=n+1,c=e[n];if(c===null||c&&r==c.key&&l===c.type&&!(131072&c.__u))return n;if(o>(c!=null&&!(131072&c.__u)?1:0))for(;d>=0||a<e.length;){if(d>=0){if((c=e[d])&&!(131072&c.__u)&&r==c.key&&l===c.type)return d;d--}if(a<e.length){if((c=e[a])&&!(131072&c.__u)&&r==c.key&&l===c.type)return a;a++}}return-1}function re(t,e,n){e[0]==="-"?t.setProperty(e,n??""):t[e]=n==null?"":typeof n!="number"||Ae.test(e)?n:n+"px"}function D(t,e,n,o,r){var l;e:if(e==="style")if(typeof n=="string")t.style.cssText=n;else{if(typeof o=="string"&&(t.style.cssText=o=""),o)for(e in o)n&&e in n||re(t.style,e,"");if(n)for(e in n)o&&n[e]===o[e]||re(t.style,e,n[e])}else if(e[0]==="o"&&e[1]==="n")l=e!==(e=e.replace(/(PointerCapture)$|Capture$/i,"$1")),e=e.toLowerCase()in t||e==="onFocusOut"||e==="onFocusIn"?e.toLowerCase().slice(2):e.slice(2),t.l||(t.l={}),t.l[e+l]=n,n?o?n.u=o.u:(n.u=Y,t.addEventListener(e,l?K:J,l)):t.removeEventListener(e,l?K:J,l);else{if(r=="http://www.w3.org/2000/svg")e=e.replace(/xlink(H|:h)/,"h").replace(/sName$/,"s");else if(e!="width"&&e!="height"&&e!="href"&&e!="list"&&e!="form"&&e!="tabIndex"&&e!="download"&&e!="rowSpan"&&e!="colSpan"&&e!="role"&&e!="popover"&&e in t)try{t[e]=n??"";break e}catch{}typeof n=="function"||(n==null||n===!1&&e[4]!=="-"?t.removeAttribute(e):t.setAttribute(e,e=="popover"&&n==1?"":n))}}function _e(t){return function(e){if(this.l){var n=this.l[e.type+t];if(e.t==null)e.t=Y++;else if(e.t<n.u)return;return n(v.event?v.event(e):e)}}}function X(t,e,n,o,r,l,d,a,c,s){var p,_,f,u,h,m,x,g,y,P,C,O,M,te,H,z,k=e.type;if(e.constructor!==void 0)return null;128&n.__u&&(c=!!(32&n.__u),l=[a=e.__e=n.__e]),(p=v.__b)&&p(e);e:if(typeof k=="function")try{if(g=e.props,y="prototype"in k&&k.prototype.render,P=(p=k.contextType)&&o[p.__c],C=p?P?P.props.value:p.__:o,n.__c?x=(_=e.__c=n.__c).__=_.__E:(y?e.__c=_=new k(g,C):(e.__c=_=new F(g,C),_.constructor=k,_.render=Oe),P&&P.sub(_),_.props=g,_.state||(_.state={}),_.context=C,_.__n=o,f=_.__d=!0,_.__h=[],_._sb=[]),y&&_.__s==null&&(_.__s=_.state),y&&k.getDerivedStateFromProps!=null&&(_.__s==_.state&&(_.__s=S({},_.__s)),S(_.__s,k.getDerivedStateFromProps(g,_.__s))),u=_.props,h=_.state,_.__v=e,f)y&&k.getDerivedStateFromProps==null&&_.componentWillMount!=null&&_.componentWillMount(),y&&_.componentDidMount!=null&&_.__h.push(_.componentDidMount);else{if(y&&k.getDerivedStateFromProps==null&&g!==u&&_.componentWillReceiveProps!=null&&_.componentWillReceiveProps(g,C),!_.__e&&(_.shouldComponentUpdate!=null&&_.shouldComponentUpdate(g,_.__s,C)===!1||e.__v===n.__v)){for(e.__v!==n.__v&&(_.props=g,_.state=_.__s,_.__d=!1),e.__e=n.__e,e.__k=n.__k,e.__k.some(function(L){L&&(L.__=e)}),O=0;O<_._sb.length;O++)_.__h.push(_._sb[O]);_._sb=[],_.__h.length&&d.push(_);break e}_.componentWillUpdate!=null&&_.componentWillUpdate(g,_.__s,C),y&&_.componentDidUpdate!=null&&_.__h.push(function(){_.componentDidUpdate(u,h,m)})}if(_.context=C,_.props=g,_.__P=t,_.__e=!1,M=v.__r,te=0,y){for(_.state=_.__s,_.__d=!1,M&&M(e),p=_.render(_.props,_.state,_.context),H=0;H<_._sb.length;H++)_.__h.push(_._sb[H]);_._sb=[]}else do _.__d=!1,M&&M(e),p=_.render(_.props,_.state,_.context),_.state=_.__s;while(_.__d&&++te<25);_.state=_.__s,_.getChildContext!=null&&(o=S(S({},o),_.getChildContext())),y&&!f&&_.getSnapshotBeforeUpdate!=null&&(m=_.getSnapshotBeforeUpdate(u,h)),ye(t,Q(z=p!=null&&p.type===E&&p.key==null?p.props.children:p)?z:[z],e,n,o,r,l,d,a,c,s),_.base=e.__e,e.__u&=-161,_.__h.length&&d.push(_),x&&(_.__E=_.__=null)}catch(L){if(e.__v=null,c||l!=null){for(e.__u|=c?160:32;a&&a.nodeType===8&&a.nextSibling;)a=a.nextSibling;l[l.indexOf(a)]=null,e.__e=a}else e.__e=n.__e,e.__k=n.__k;v.__e(L,e,n)}else l==null&&e.__v===n.__v?(e.__k=n.__k,e.__e=n.__e):e.__e=Ee(n.__e,e,n,o,r,l,d,c,s);(p=v.diffed)&&p(e)}function we(t,e,n){e.__d=void 0;for(var o=0;o<n.length;o++)Z(n[o],n[++o],n[++o]);v.__c&&v.__c(e,t),t.some(function(r){try{t=r.__h,r.__h=[],t.some(function(l){l.call(r)})}catch(l){v.__e(l,r.__v)}})}function Ee(t,e,n,o,r,l,d,a,c){var s,p,_,f,u,h,m,x=n.props,g=e.props,y=e.type;if(y==="svg"?r="http://www.w3.org/2000/svg":y==="math"?r="http://www.w3.org/1998/Math/MathML":r||(r="http://www.w3.org/1999/xhtml"),l!=null){for(s=0;s<l.length;s++)if((u=l[s])&&"setAttribute"in u==!!y&&(y?u.localName===y:u.nodeType===3)){t=u,l[s]=null;break}}if(t==null){if(y===null)return document.createTextNode(g);t=document.createElementNS(r,y,g.is&&g),a&&(v.__m&&v.__m(e,l),a=!1),l=null}if(y===null)x===g||a&&t.data===g||(t.data=g);else{if(l=l&&B.call(t.childNodes),x=n.props||$,!a&&l!=null)for(x={},s=0;s<t.attributes.length;s++)x[(u=t.attributes[s]).name]=u.value;for(s in x)if(u=x[s],s!="children"){if(s=="dangerouslySetInnerHTML")_=u;else if(!(s in g)){if(s=="value"&&"defaultValue"in g||s=="checked"&&"defaultChecked"in g)continue;D(t,s,null,u,r)}}for(s in g)u=g[s],s=="children"?f=u:s=="dangerouslySetInnerHTML"?p=u:s=="value"?h=u:s=="checked"?m=u:a&&typeof u!="function"||x[s]===u||D(t,s,u,x[s],r);if(p)a||_&&(p.__html===_.__html||p.__html===t.innerHTML)||(t.innerHTML=p.__html),e.__k=[];else if(_&&(t.innerHTML=""),ye(t,Q(f)?f:[f],e,n,o,y==="foreignObject"?"http://www.w3.org/1999/xhtml":r,l,d,l?l[0]:n.__k&&A(n,0),a,c),l!=null)for(s=l.length;s--;)ve(l[s]);a||(s="value",y==="progress"&&h==null?t.removeAttribute("value"):h!==void 0&&(h!==t[s]||y==="progress"&&!h||y==="option"&&h!==x[s])&&D(t,s,h,x[s],r),s="checked",m!==void 0&&m!==t[s]&&D(t,s,m,x[s],r))}return t}function Z(t,e,n){try{if(typeof t=="function"){var o=typeof t.__u=="function";o&&t.__u(),o&&e==null||(t.__u=t(e))}else t.current=e}catch(r){v.__e(r,n)}}function xe(t,e,n){var o,r;if(v.unmount&&v.unmount(t),(o=t.ref)&&(o.current&&o.current!==t.__e||Z(o,null,e)),(o=t.__c)!=null){if(o.componentWillUnmount)try{o.componentWillUnmount()}catch(l){v.__e(l,e)}o.base=o.__P=null}if(o=t.__k)for(r=0;r<o.length;r++)o[r]&&xe(o[r],e,n||typeof t.type!="function");n||ve(t.__e),t.__c=t.__=t.__e=t.__d=void 0}function Oe(t,e,n){return this.constructor(t,n)}function He(t,e,n){var o,r,l,d;v.__&&v.__(t,e),r=(o=typeof n=="function")?null:e.__k,l=[],d=[],X(e,t=(!o&&n||e).__k=Pe(E,null,[t]),r||$,$,e.namespaceURI,!o&&n?[n]:r?null:e.firstChild?B.call(e.childNodes):null,l,!o&&n?n:r?r.__e:e.firstChild,o,d),we(l,t,d)}B=me.slice,v={__e:function(t,e,n,o){for(var r,l,d;e=e.__;)if((r=e.__c)&&!r.__)try{if((l=r.constructor)&&l.getDerivedStateFromError!=null&&(r.setState(l.getDerivedStateFromError(t)),d=r.__d),r.componentDidCatch!=null&&(r.componentDidCatch(t,o||{}),d=r.__d),d)return r.__E=r}catch(a){t=a}throw t}},he=0,F.prototype.setState=function(t,e){var n;n=this.__s!=null&&this.__s!==this.state?this.__s:this.__s=S({},this.state),typeof t=="function"&&(t=t(S({},n),this.props)),t&&S(n,t),t!=null&&this.__v&&(e&&this._sb.push(e),oe(this))},F.prototype.forceUpdate=function(t){this.__v&&(this.__e=!0,t&&this.__h.push(t),oe(this))},F.prototype.render=E,T=[],pe=typeof Promise=="function"?Promise.prototype.then.bind(Promise.resolve()):setTimeout,q=function(t,e){return t.__v.__b-e.__v.__b},U.__r=0,Y=0,J=_e(!1),K=_e(!0);var Le=0;function i(t,e,n,o,r,l){e||(e={});var d,a,c=e;if("ref"in c)for(a in c={},e)a=="ref"?d=e[a]:c[a]=e[a];var s={type:t,props:c,key:n,ref:d,__k:null,__:null,__b:0,__e:null,__d:void 0,__c:null,constructor:void 0,__v:--Le,__i:-1,__u:0,__source:r,__self:l};if(typeof t=="function"&&(d=t.defaultProps))for(a in d)c[a]===void 0&&(c[a]=d[a]);return v.vnode&&v.vnode(s),s}var W,b,R,le,G=0,ke=[],w=v,ie=w.__b,ae=w.__r,se=w.diffed,ce=w.__c,de=w.unmount,ue=w.__;function Ne(t,e){w.__h&&w.__h(b,t,G||e),G=0;var n=b.__H||(b.__H={__:[],__h:[]});return t>=n.__.length&&n.__.push({}),n.__[t]}function N(t){return G=1,De(Ce,t)}function De(t,e,n){var o=Ne(W++,2);if(o.t=t,!o.__c&&(o.__=[Ce(void 0,e),function(a){var c=o.__N?o.__N[0]:o.__[0],s=o.t(c,a);c!==s&&(o.__N=[s,o.__[1]],o.__c.setState({}))}],o.__c=b,!b.u)){var r=function(a,c,s){if(!o.__c.__H)return!0;var p=o.__c.__H.__.filter(function(f){return!!f.__c});if(p.every(function(f){return!f.__N}))return!l||l.call(this,a,c,s);var _=!1;return p.forEach(function(f){if(f.__N){var u=f.__[0];f.__=f.__N,f.__N=void 0,u!==f.__[0]&&(_=!0)}}),!(!_&&o.__c.props===a)&&(!l||l.call(this,a,c,s))};b.u=!0;var l=b.shouldComponentUpdate,d=b.componentWillUpdate;b.componentWillUpdate=function(a,c,s){if(this.__e){var p=l;l=void 0,r(a,c,s),l=p}d&&d.call(this,a,c,s)},b.shouldComponentUpdate=r}return o.__N||o.__}function ee(t,e){var n=Ne(W++,3);!w.__s&&Ie(n.__H,e)&&(n.__=t,n.i=e,b.__H.__h.push(n))}function je(){for(var t;t=ke.shift();)if(t.__P&&t.__H)try{t.__H.__h.forEach(I),t.__H.__h.forEach(V),t.__H.__h=[]}catch(e){t.__H.__h=[],w.__e(e,t.__v)}}w.__b=function(t){b=null,ie&&ie(t)},w.__=function(t,e){t&&e.__k&&e.__k.__m&&(t.__m=e.__k.__m),ue&&ue(t,e)},w.__r=function(t){ae&&ae(t),W=0;var e=(b=t.__c).__H;e&&(R===b?(e.__h=[],b.__h=[],e.__.forEach(function(n){n.__N&&(n.__=n.__N),n.i=n.__N=void 0})):(e.__h.forEach(I),e.__h.forEach(V),e.__h=[],W=0)),R=b},w.diffed=function(t){se&&se(t);var e=t.__c;e&&e.__H&&(e.__H.__h.length&&(ke.push(e)!==1&&le===w.requestAnimationFrame||((le=w.requestAnimationFrame)||Fe)(je)),e.__H.__.forEach(function(n){n.i&&(n.__H=n.i),n.i=void 0})),R=b=null},w.__c=function(t,e){e.some(function(n){try{n.__h.forEach(I),n.__h=n.__h.filter(function(o){return!o.__||V(o)})}catch(o){e.some(function(r){r.__h&&(r.__h=[])}),e=[],w.__e(o,n.__v)}}),ce&&ce(t,e)},w.unmount=function(t){de&&de(t);var e,n=t.__c;n&&n.__H&&(n.__H.__.forEach(function(o){try{I(o)}catch(r){e=r}}),n.__H=void 0,e&&w.__e(e,n.__v))};var fe=typeof requestAnimationFrame=="function";function Fe(t){var e,n=function(){clearTimeout(o),fe&&cancelAnimationFrame(e),setTimeout(t)},o=setTimeout(n,100);fe&&(e=requestAnimationFrame(n))}function I(t){var e=b,n=t.__c;typeof n=="function"&&(t.__c=void 0,n()),b=e}function V(t){var e=b;t.__c=t.__(),b=e}function Ie(t,e){return!t||t.length!==e.length||e.some(function(n,o){return n!==t[o]})}function Ce(t,e){return typeof e=="function"?e(t):e}const Ue=["light","dark","cupcake","bumblebee","emerald","corporate","synthwave","retro","cyberpunk","valentine","halloween","garden","forest","aqua","lofi","pastel","fantasy","wireframe","black","luxury","dracula","cmyk","autumn","business","acid","lemonade","night","coffee","winter","dim","nord","sunset"],We=()=>i("svg",{xmlns:"http://www.w3.org/2000/svg",width:"24",height:"24",viewBox:"0 0 24 24",fill:"none",stroke:"currentColor","stroke-width":"2","stroke-linecap":"round","stroke-linejoin":"round",children:i("path",{d:"M12 3v1M12 20v1M4.22 4.22l.71.71M19.07 19.07l.71.71M1 12h1M22 12h1M4.22 19.78l.71-.71M19.07 4.93l.71-.71M12 5a7 7 0 1 1 0 14 7 7 0 0 1 0-14z"})}),Be=()=>i("svg",{xmlns:"http://www.w3.org/2000/svg",className:"h-4 w-4",viewBox:"0 0 20 20",fill:"currentColor",children:i("path",{fillRule:"evenodd",d:"M16.707 5.293a1 1 0 00-1.414 0L8 12.586 4.707 9.293a1 1 0 00-1.414 1.414l4 4a1 1 0 001.414 0l8-8a1 1 0 000-1.414z",clipRule:"evenodd"})});function ze(){const[t,e]=N("light");ee(()=>{const o=localStorage.getItem("selectedTheme");o&&(e(o),document.documentElement.setAttribute("data-theme",o))},[]);const n=o=>{e(o),document.documentElement.setAttribute("data-theme",o),localStorage.setItem("selectedTheme",o)};return i("div",{className:"navbar bg-base-100 w-full max-h-2 z-50",children:[i("div",{className:"flex-1",children:i("a",{className:"btn btn-ghost text-xl pl-2",children:"School Bell"})}),i("div",{className:"flex-none",children:i("div",{className:"dropdown dropdown-end",children:[i("label",{tabIndex:0,className:"btn btn-ghost m-1",children:i(We,{})}),i("div",{tabIndex:0,className:"dropdown-content bg-base-100 p-2 text-base-content rounded-box top-px h-[28.6rem] max-h-[calc(100vh-10rem)] w-56 overflow-y-auto border border-white/5 shadow-2xl outline outline-1 outline-black/5 mt-16 z-50",children:Ue.map(o=>i("button",{className:"btn w-full text-left mb-2 capitalize flex justify-between items-center","data-theme":o,onClick:()=>n(o),children:[i("div",{className:"flex items-center space-x-2",children:[t===o&&i(Be,{}),i("span",{children:o})]}),i("div",{className:"flex space-x-1",children:[i("div",{className:"w-2 h-4 rounded-full bg-primary"}),i("div",{className:"w-2 h-4 rounded-full bg-secondary"}),i("div",{className:"w-2 h-4 rounded-full bg-accent"}),i("div",{className:"w-2 h-4 rounded-full bg-neutral"})]})]},o))})]})})]})}const Re=({id:t,time:e,label:n,active:o,repeat:r,onDelete:l,onToggle:d,onClick:a})=>{const[c,s]=N(o),p=r.split(","),_=["S","M","T","W","T","F","S"],f=h=>{h.stopPropagation(),a()},u=h=>{h.stopPropagation();const m=!c;s(m),d(m)};return i("div",{className:"relative",children:i("div",{className:`card ${c?"bg-neutral":"bg-base-300"} no-animation text-neutral-content p-2 w-40 h-40 relative cursor-pointer`,onClick:f,children:[i("h2",{className:`text-sm text-left ${c?"text-neutral-content":"text-base-content"}`,children:n}),i("p",{className:`text-5xl font-bold mb-3 mt-2 text-center ${c?"text-neutral-content":"text-base-content"}`,children:e}),i("div",{className:"flex justify-between mb-2",children:_.map((h,m)=>i("div",{className:`w-5 h-5 flex items-center justify-center rounded-full ${p.includes(m.toString())?"bg-accent text-accent-content":"bg-ghost text-neutral-content"}`,children:i("span",{className:"text-xs",children:h})},m))}),i("button",{className:"btn btn-error btn-square btn-xs absolute bottom-2",onClick:h=>{h.stopPropagation(),l()},children:i("svg",{xmlns:"http://www.w3.org/2000/svg",className:"h-6 w-6",fill:"none",viewBox:"0 0 24 24",stroke:"currentColor",children:i("path",{strokeLinecap:"round",strokeLinejoin:"round",strokeWidth:"2",d:"M6 18L18 6M6 6l12 12"})})}),i("div",{className:"absolute bottom-0 right-3",onClick:u,children:i("input",{type:"checkbox",className:"toggle toggle-accent",checked:c,onChange:()=>{}})})]})})},Se=({initialTime:t="12:00",initialLabel:e="",initialActiveDays:n=[],onCancel:o,onOk:r})=>{const[l,d]=N(t),[a,c]=N(e),[s,p]=N(n),_=["S","M","T","W","T","F","S"],f=h=>{p(m=>m.includes(h.toString())?m.filter(x=>x!==h.toString()):[...m,h.toString()])},u=()=>{r(l,a,s)};return i("div",{className:"fixed inset-0 flex items-center justify-center bg-black bg-opacity-50 z-50",children:i("div",{className:"modal modal-open",children:i("div",{className:"modal-box",children:[i("h2",{className:"font-semibold text-lg mb-2",children:"Label"}),i("input",{type:"text",placeholder:"Type here",className:"input input-bordered w-full",value:a,onChange:h=>c(h.target.value)}),i("h2",{className:"font-semibold text-lg mb-2 mt-4",children:"Select Time"}),i("input",{type:"time",value:l,onChange:h=>d(h.target.value),className:"input input-bordered w-full"}),i("h2",{className:"font-semibold text-lg mb-2 mt-4",children:"Repeat"}),i("div",{className:"flex justify-between mb-2",children:_.map((h,m)=>i("label",{className:"swap swap-flip",children:[i("input",{type:"checkbox",checked:s.includes(m.toString()),onChange:()=>f(m)}),i("div",{className:"swap-on w-8 h-8 flex items-center justify-center bg-accent text-accent-content rounded-full",children:i("span",{className:"text-xs",children:h})}),i("div",{className:"swap-off w-8 h-8 flex items-center justify-center bg-base-300 text-base-content rounded-full",children:i("span",{className:"text-xs",children:h})})]},m))}),i("div",{className:"modal-action",children:[i("button",{className:"btn",onClick:o,children:"Cancel"}),i("button",{className:"btn btn-accent",onClick:u,children:"OK"})]})]})})})},qe=({onAdd:t})=>{const[e,n]=N(!1);return i("div",{className:"relative",children:[i("div",{className:"card bg-ghost no-animation text-neutral-content p-4 w-40 h-40 relative cursor-pointer border-dashed border-2 border-gray-400 flex items-center justify-center",onClick:()=>{n(!0)},children:i("h1",{className:"text-6xl text-base-content",children:"+"})}),e&&i(Se,{onCancel:()=>{n(!1)},onOk:(d,a,c)=>{t(d,a,c),n(!1)}})]})},Te=()=>{const[t,e]=N(new Date);ee(()=>{const _=setInterval(()=>{e(new Date)},1e3);return()=>clearInterval(_)},[]);const n=["Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"],o=["Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"],r=n[t.getDay()],l=String(t.getHours()).padStart(2,"0"),d=String(t.getMinutes()).padStart(2,"0"),a=String(t.getSeconds()).padStart(2,"0"),c=t.getDate(),s=o[t.getMonth()],p=t.getFullYear();return i("div",{className:"grid grid-cols-2 gap-0 px-4 mb-6",children:[i("div",{className:"flex flex-col justify-start",children:[i("h3",{className:"text-sm text-accent font-semibold",children:"Good Morning,"}),i("h1",{className:"text-4xl font-semibold",children:"Kamisato"})]}),i("div",{className:"flex flex-col justify-end items-end",children:[i("h3",{className:"text-sm text-accent font-semibold",children:[r,", ",c," ",s," ",p]}),i("div",{className:"text-4xl font-semibold",children:[i("span",{children:l}),i("span",{className:"blink",children:":"}),i("span",{children:d}),i("span",{className:"blink",children:":"}),i("span",{children:a})]})]})]})},Je=()=>{const[t,e]=N([]),[n,o]=N(null);ee(()=>{r()},[]);const r=async()=>{try{const f=await(await fetch("/api/get")).json();e(f)}catch(_){console.error("Error fetching alarms:",_)}},l=async(_,f,u)=>{try{(await fetch("/api/add",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify({time:_,label:f,repeat:u.join(",")})})).ok&&r()}catch(h){console.error("Error adding alarm:",h)}},d=async(_,f,u,h)=>{try{(await fetch("/api/update",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify({id:_,time:f,label:u,repeat:h.join(",")})})).ok&&r()}catch(m){console.error("Error updating alarm:",m)}o(null)},a=async _=>{try{(await fetch("/api/delete",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify({id:_})})).ok&&r()}catch(f){console.error("Error deleting alarm:",f)}},c=async(_,f)=>{try{(await fetch("/api/toggle",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify({id:_,isActive:f})})).ok&&r()}catch(u){console.error("Error toggling alarm:",u)}},s=_=>{o(_)},p=async()=>{try{(await fetch("/api/update_all",{method:"POST",headers:{"Content-Type":"application/json"},body:JSON.stringify(t)})).ok&&r()}catch(_){console.error("Error updating alarms:",_)}};return i("div",{className:"container mx-auto p-4",children:[i(Te,{}),i("div",{className:"grid grid-cols-2 gap-4 lg:gap-12 place-items-center md:grid-cols-4 lg:grid-cols-5",children:[t.map(_=>i(Re,{..._,onDelete:()=>a(_.id),onToggle:f=>c(_.id,f),onClick:()=>s(_)},_.id)),i(qe,{onAdd:l})]}),n&&i(Se,{initialTime:n.time,initialLabel:n.label,initialActiveDays:n.repeat.split(","),onCancel:()=>o(null),onOk:(_,f,u)=>d(n.id,_,f,u)}),i("div",{className:"mt-8 text-center",children:i("button",{className:"btn btn-primary",onClick:p,children:"Update and Save Alarms"})})]})};function Ke(){return i(E,{children:[i(ze,{}),i(Te,{}),i(Je,{})]})}He(i(Ke,{}),document.getElementById("app"));
