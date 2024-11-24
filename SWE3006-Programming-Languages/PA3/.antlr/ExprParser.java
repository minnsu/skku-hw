// Generated from /root/PA3/Expr.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class ExprParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, ID=15, INT=16, REAL=17, 
		NEWLINE=18, WS=19;
	public static final int
		RULE_prog = 0, RULE_decl = 1, RULE_prior_expr = 2, RULE_expr = 3, RULE_var = 4, 
		RULE_number = 5;
	private static String[] makeRuleNames() {
		return new String[] {
			"prog", "decl", "prior_expr", "expr", "var", "number"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "';'", "'def'", "'='", "'endef'", "'let'", "'in'", "'('", "','", 
			"')'", "'*'", "'/'", "'+'", "'-'", "'~'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, "ID", "INT", "REAL", "NEWLINE", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "Expr.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public ExprParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProgContext extends ParserRuleContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public List<DeclContext> decl() {
			return getRuleContexts(DeclContext.class);
		}
		public DeclContext decl(int i) {
			return getRuleContext(DeclContext.class,i);
		}
		public ProgContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_prog; }
	}

	public final ProgContext prog() throws RecognitionException {
		ProgContext _localctx = new ProgContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_prog);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(15);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__1) {
				{
				{
				setState(12);
				decl();
				}
				}
				setState(17);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(18);
			expr(0);
			setState(19);
			match(T__0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class DeclContext extends ParserRuleContext {
		public List<VarContext> var() {
			return getRuleContexts(VarContext.class);
		}
		public VarContext var(int i) {
			return getRuleContext(VarContext.class,i);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public DeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_decl; }
	}

	public final DeclContext decl() throws RecognitionException {
		DeclContext _localctx = new DeclContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(21);
			match(T__1);
			setState(22);
			var();
			setState(26);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==ID) {
				{
				{
				setState(23);
				var();
				}
				}
				setState(28);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(29);
			match(T__2);
			setState(30);
			expr(0);
			setState(31);
			match(T__3);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Prior_exprContext extends ParserRuleContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public Prior_exprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_prior_expr; }
	}

	public final Prior_exprContext prior_expr() throws RecognitionException {
		Prior_exprContext _localctx = new Prior_exprContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_prior_expr);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(33);
			expr(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExprContext extends ParserRuleContext {
		public ExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr; }
	 
		public ExprContext() { }
		public void copyFrom(ExprContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class LetinExprContext extends ExprContext {
		public VarContext var() {
			return getRuleContext(VarContext.class,0);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public Prior_exprContext prior_expr() {
			return getRuleContext(Prior_exprContext.class,0);
		}
		public LetinExprContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class VarExprContext extends ExprContext {
		public VarContext var() {
			return getRuleContext(VarContext.class,0);
		}
		public VarExprContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class InfixExprContext extends ExprContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public InfixExprContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class NegationExprContext extends ExprContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public NegationExprContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class NumberExprContext extends ExprContext {
		public NumberContext number() {
			return getRuleContext(NumberContext.class,0);
		}
		public NumberExprContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class CallExprContext extends ExprContext {
		public VarContext var() {
			return getRuleContext(VarContext.class,0);
		}
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public CallExprContext(ExprContext ctx) { copyFrom(ctx); }
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ParenExprContext extends ExprContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public ParenExprContext(ExprContext ctx) { copyFrom(ctx); }
	}

	public final ExprContext expr() throws RecognitionException {
		return expr(0);
	}

	private ExprContext expr(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ExprContext _localctx = new ExprContext(_ctx, _parentState);
		ExprContext _prevctx = _localctx;
		int _startState = 6;
		enterRecursionRule(_localctx, 6, RULE_expr, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(68);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,4,_ctx) ) {
			case 1:
				{
				_localctx = new LetinExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(36);
				match(T__4);
				setState(37);
				var();
				setState(38);
				match(T__2);
				setState(39);
				expr(0);
				setState(40);
				match(T__5);
				setState(41);
				prior_expr();
				}
				break;
			case 2:
				{
				_localctx = new CallExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(43);
				var();
				setState(44);
				match(T__6);
				setState(53);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 254112L) != 0)) {
					{
					setState(45);
					expr(0);
					setState(50);
					_errHandler.sync(this);
					_la = _input.LA(1);
					while (_la==T__7) {
						{
						{
						setState(46);
						match(T__7);
						setState(47);
						expr(0);
						}
						}
						setState(52);
						_errHandler.sync(this);
						_la = _input.LA(1);
					}
					}
				}

				setState(55);
				match(T__8);
				}
				break;
			case 3:
				{
				_localctx = new ParenExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(57);
				match(T__6);
				setState(58);
				expr(0);
				setState(59);
				match(T__8);
				}
				break;
			case 4:
				{
				_localctx = new NumberExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(61);
				number();
				}
				break;
			case 5:
				{
				_localctx = new NegationExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(62);
				match(T__13);
				setState(63);
				match(T__6);
				setState(64);
				expr(0);
				setState(65);
				match(T__8);
				}
				break;
			case 6:
				{
				_localctx = new VarExprContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(67);
				var();
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(78);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,6,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(76);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,5,_ctx) ) {
					case 1:
						{
						_localctx = new InfixExprContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(70);
						if (!(precpred(_ctx, 6))) throw new FailedPredicateException(this, "precpred(_ctx, 6)");
						setState(71);
						_la = _input.LA(1);
						if ( !(_la==T__9 || _la==T__10) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(72);
						expr(7);
						}
						break;
					case 2:
						{
						_localctx = new InfixExprContext(new ExprContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_expr);
						setState(73);
						if (!(precpred(_ctx, 5))) throw new FailedPredicateException(this, "precpred(_ctx, 5)");
						setState(74);
						_la = _input.LA(1);
						if ( !(_la==T__11 || _la==T__12) ) {
						_errHandler.recoverInline(this);
						}
						else {
							if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
							_errHandler.reportMatch(this);
							consume();
						}
						setState(75);
						expr(6);
						}
						break;
					}
					} 
				}
				setState(80);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,6,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class VarContext extends ParserRuleContext {
		public TerminalNode ID() { return getToken(ExprParser.ID, 0); }
		public VarContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_var; }
	}

	public final VarContext var() throws RecognitionException {
		VarContext _localctx = new VarContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_var);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(81);
			match(ID);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class NumberContext extends ParserRuleContext {
		public TerminalNode INT() { return getToken(ExprParser.INT, 0); }
		public TerminalNode REAL() { return getToken(ExprParser.REAL, 0); }
		public NumberContext number() {
			return getRuleContext(NumberContext.class,0);
		}
		public NumberContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_number; }
	}

	public final NumberContext number() throws RecognitionException {
		NumberContext _localctx = new NumberContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_number);
		try {
			setState(87);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case INT:
				enterOuterAlt(_localctx, 1);
				{
				setState(83);
				match(INT);
				}
				break;
			case REAL:
				enterOuterAlt(_localctx, 2);
				{
				setState(84);
				match(REAL);
				}
				break;
			case T__12:
				enterOuterAlt(_localctx, 3);
				{
				setState(85);
				match(T__12);
				setState(86);
				number();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 3:
			return expr_sempred((ExprContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean expr_sempred(ExprContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 6);
		case 1:
			return precpred(_ctx, 5);
		}
		return true;
	}

	public static final String _serializedATN =
		"\u0004\u0001\u0013Z\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0001\u0000\u0005\u0000\u000e\b\u0000\n\u0000\f\u0000"+
		"\u0011\t\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0005\u0001\u0019\b\u0001\n\u0001\f\u0001\u001c\t\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0002\u0001\u0002\u0001"+
		"\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001"+
		"\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001"+
		"\u0003\u0005\u00031\b\u0003\n\u0003\f\u00034\t\u0003\u0003\u00036\b\u0003"+
		"\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0003\u0003\u0003E\b\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0003\u0001\u0003\u0001\u0003\u0005\u0003M\b\u0003\n\u0003\f\u0003"+
		"P\t\u0003\u0001\u0004\u0001\u0004\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0003\u0005X\b\u0005\u0001\u0005\u0000\u0001\u0006\u0006"+
		"\u0000\u0002\u0004\u0006\b\n\u0000\u0002\u0001\u0000\n\u000b\u0001\u0000"+
		"\f\r`\u0000\u000f\u0001\u0000\u0000\u0000\u0002\u0015\u0001\u0000\u0000"+
		"\u0000\u0004!\u0001\u0000\u0000\u0000\u0006D\u0001\u0000\u0000\u0000\b"+
		"Q\u0001\u0000\u0000\u0000\nW\u0001\u0000\u0000\u0000\f\u000e\u0003\u0002"+
		"\u0001\u0000\r\f\u0001\u0000\u0000\u0000\u000e\u0011\u0001\u0000\u0000"+
		"\u0000\u000f\r\u0001\u0000\u0000\u0000\u000f\u0010\u0001\u0000\u0000\u0000"+
		"\u0010\u0012\u0001\u0000\u0000\u0000\u0011\u000f\u0001\u0000\u0000\u0000"+
		"\u0012\u0013\u0003\u0006\u0003\u0000\u0013\u0014\u0005\u0001\u0000\u0000"+
		"\u0014\u0001\u0001\u0000\u0000\u0000\u0015\u0016\u0005\u0002\u0000\u0000"+
		"\u0016\u001a\u0003\b\u0004\u0000\u0017\u0019\u0003\b\u0004\u0000\u0018"+
		"\u0017\u0001\u0000\u0000\u0000\u0019\u001c\u0001\u0000\u0000\u0000\u001a"+
		"\u0018\u0001\u0000\u0000\u0000\u001a\u001b\u0001\u0000\u0000\u0000\u001b"+
		"\u001d\u0001\u0000\u0000\u0000\u001c\u001a\u0001\u0000\u0000\u0000\u001d"+
		"\u001e\u0005\u0003\u0000\u0000\u001e\u001f\u0003\u0006\u0003\u0000\u001f"+
		" \u0005\u0004\u0000\u0000 \u0003\u0001\u0000\u0000\u0000!\"\u0003\u0006"+
		"\u0003\u0000\"\u0005\u0001\u0000\u0000\u0000#$\u0006\u0003\uffff\uffff"+
		"\u0000$%\u0005\u0005\u0000\u0000%&\u0003\b\u0004\u0000&\'\u0005\u0003"+
		"\u0000\u0000\'(\u0003\u0006\u0003\u0000()\u0005\u0006\u0000\u0000)*\u0003"+
		"\u0004\u0002\u0000*E\u0001\u0000\u0000\u0000+,\u0003\b\u0004\u0000,5\u0005"+
		"\u0007\u0000\u0000-2\u0003\u0006\u0003\u0000./\u0005\b\u0000\u0000/1\u0003"+
		"\u0006\u0003\u00000.\u0001\u0000\u0000\u000014\u0001\u0000\u0000\u0000"+
		"20\u0001\u0000\u0000\u000023\u0001\u0000\u0000\u000036\u0001\u0000\u0000"+
		"\u000042\u0001\u0000\u0000\u00005-\u0001\u0000\u0000\u000056\u0001\u0000"+
		"\u0000\u000067\u0001\u0000\u0000\u000078\u0005\t\u0000\u00008E\u0001\u0000"+
		"\u0000\u00009:\u0005\u0007\u0000\u0000:;\u0003\u0006\u0003\u0000;<\u0005"+
		"\t\u0000\u0000<E\u0001\u0000\u0000\u0000=E\u0003\n\u0005\u0000>?\u0005"+
		"\u000e\u0000\u0000?@\u0005\u0007\u0000\u0000@A\u0003\u0006\u0003\u0000"+
		"AB\u0005\t\u0000\u0000BE\u0001\u0000\u0000\u0000CE\u0003\b\u0004\u0000"+
		"D#\u0001\u0000\u0000\u0000D+\u0001\u0000\u0000\u0000D9\u0001\u0000\u0000"+
		"\u0000D=\u0001\u0000\u0000\u0000D>\u0001\u0000\u0000\u0000DC\u0001\u0000"+
		"\u0000\u0000EN\u0001\u0000\u0000\u0000FG\n\u0006\u0000\u0000GH\u0007\u0000"+
		"\u0000\u0000HM\u0003\u0006\u0003\u0007IJ\n\u0005\u0000\u0000JK\u0007\u0001"+
		"\u0000\u0000KM\u0003\u0006\u0003\u0006LF\u0001\u0000\u0000\u0000LI\u0001"+
		"\u0000\u0000\u0000MP\u0001\u0000\u0000\u0000NL\u0001\u0000\u0000\u0000"+
		"NO\u0001\u0000\u0000\u0000O\u0007\u0001\u0000\u0000\u0000PN\u0001\u0000"+
		"\u0000\u0000QR\u0005\u000f\u0000\u0000R\t\u0001\u0000\u0000\u0000SX\u0005"+
		"\u0010\u0000\u0000TX\u0005\u0011\u0000\u0000UV\u0005\r\u0000\u0000VX\u0003"+
		"\n\u0005\u0000WS\u0001\u0000\u0000\u0000WT\u0001\u0000\u0000\u0000WU\u0001"+
		"\u0000\u0000\u0000X\u000b\u0001\u0000\u0000\u0000\b\u000f\u001a25DLNW";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}