// Generated from /root/PA3/Expr.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class ExprLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, ID=15, INT=16, REAL=17, 
		NEWLINE=18, WS=19;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
			"T__9", "T__10", "T__11", "T__12", "T__13", "ID", "INT", "REAL", "NEWLINE", 
			"WS"
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


	public ExprLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "Expr.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\u0004\u0000\u0013n\u0006\uffff\uffff\u0002\u0000\u0007\u0000\u0002\u0001"+
		"\u0007\u0001\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004"+
		"\u0007\u0004\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007"+
		"\u0007\u0007\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b"+
		"\u0007\u000b\u0002\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002"+
		"\u000f\u0007\u000f\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002"+
		"\u0012\u0007\u0012\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0002\u0001\u0002\u0001\u0003\u0001\u0003\u0001"+
		"\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0004\u0001\u0004\u0001"+
		"\u0004\u0001\u0004\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0006\u0001"+
		"\u0006\u0001\u0007\u0001\u0007\u0001\b\u0001\b\u0001\t\u0001\t\u0001\n"+
		"\u0001\n\u0001\u000b\u0001\u000b\u0001\f\u0001\f\u0001\r\u0001\r\u0001"+
		"\u000e\u0004\u000eN\b\u000e\u000b\u000e\f\u000eO\u0001\u000f\u0004\u000f"+
		"S\b\u000f\u000b\u000f\f\u000fT\u0001\u0010\u0004\u0010X\b\u0010\u000b"+
		"\u0010\f\u0010Y\u0001\u0010\u0001\u0010\u0005\u0010^\b\u0010\n\u0010\f"+
		"\u0010a\t\u0010\u0001\u0011\u0004\u0011d\b\u0011\u000b\u0011\f\u0011e"+
		"\u0001\u0012\u0004\u0012i\b\u0012\u000b\u0012\f\u0012j\u0001\u0012\u0001"+
		"\u0012\u0000\u0000\u0013\u0001\u0001\u0003\u0002\u0005\u0003\u0007\u0004"+
		"\t\u0005\u000b\u0006\r\u0007\u000f\b\u0011\t\u0013\n\u0015\u000b\u0017"+
		"\f\u0019\r\u001b\u000e\u001d\u000f\u001f\u0010!\u0011#\u0012%\u0013\u0001"+
		"\u0000\u0004\u0005\u0000-.09AZ__az\u0001\u000009\u0002\u0000\n\n\r\r\u0003"+
		"\u0000\t\n\r\r  s\u0000\u0001\u0001\u0000\u0000\u0000\u0000\u0003\u0001"+
		"\u0000\u0000\u0000\u0000\u0005\u0001\u0000\u0000\u0000\u0000\u0007\u0001"+
		"\u0000\u0000\u0000\u0000\t\u0001\u0000\u0000\u0000\u0000\u000b\u0001\u0000"+
		"\u0000\u0000\u0000\r\u0001\u0000\u0000\u0000\u0000\u000f\u0001\u0000\u0000"+
		"\u0000\u0000\u0011\u0001\u0000\u0000\u0000\u0000\u0013\u0001\u0000\u0000"+
		"\u0000\u0000\u0015\u0001\u0000\u0000\u0000\u0000\u0017\u0001\u0000\u0000"+
		"\u0000\u0000\u0019\u0001\u0000\u0000\u0000\u0000\u001b\u0001\u0000\u0000"+
		"\u0000\u0000\u001d\u0001\u0000\u0000\u0000\u0000\u001f\u0001\u0000\u0000"+
		"\u0000\u0000!\u0001\u0000\u0000\u0000\u0000#\u0001\u0000\u0000\u0000\u0000"+
		"%\u0001\u0000\u0000\u0000\u0001\'\u0001\u0000\u0000\u0000\u0003)\u0001"+
		"\u0000\u0000\u0000\u0005-\u0001\u0000\u0000\u0000\u0007/\u0001\u0000\u0000"+
		"\u0000\t5\u0001\u0000\u0000\u0000\u000b9\u0001\u0000\u0000\u0000\r<\u0001"+
		"\u0000\u0000\u0000\u000f>\u0001\u0000\u0000\u0000\u0011@\u0001\u0000\u0000"+
		"\u0000\u0013B\u0001\u0000\u0000\u0000\u0015D\u0001\u0000\u0000\u0000\u0017"+
		"F\u0001\u0000\u0000\u0000\u0019H\u0001\u0000\u0000\u0000\u001bJ\u0001"+
		"\u0000\u0000\u0000\u001dM\u0001\u0000\u0000\u0000\u001fR\u0001\u0000\u0000"+
		"\u0000!W\u0001\u0000\u0000\u0000#c\u0001\u0000\u0000\u0000%h\u0001\u0000"+
		"\u0000\u0000\'(\u0005;\u0000\u0000(\u0002\u0001\u0000\u0000\u0000)*\u0005"+
		"d\u0000\u0000*+\u0005e\u0000\u0000+,\u0005f\u0000\u0000,\u0004\u0001\u0000"+
		"\u0000\u0000-.\u0005=\u0000\u0000.\u0006\u0001\u0000\u0000\u0000/0\u0005"+
		"e\u0000\u000001\u0005n\u0000\u000012\u0005d\u0000\u000023\u0005e\u0000"+
		"\u000034\u0005f\u0000\u00004\b\u0001\u0000\u0000\u000056\u0005l\u0000"+
		"\u000067\u0005e\u0000\u000078\u0005t\u0000\u00008\n\u0001\u0000\u0000"+
		"\u00009:\u0005i\u0000\u0000:;\u0005n\u0000\u0000;\f\u0001\u0000\u0000"+
		"\u0000<=\u0005(\u0000\u0000=\u000e\u0001\u0000\u0000\u0000>?\u0005,\u0000"+
		"\u0000?\u0010\u0001\u0000\u0000\u0000@A\u0005)\u0000\u0000A\u0012\u0001"+
		"\u0000\u0000\u0000BC\u0005*\u0000\u0000C\u0014\u0001\u0000\u0000\u0000"+
		"DE\u0005/\u0000\u0000E\u0016\u0001\u0000\u0000\u0000FG\u0005+\u0000\u0000"+
		"G\u0018\u0001\u0000\u0000\u0000HI\u0005-\u0000\u0000I\u001a\u0001\u0000"+
		"\u0000\u0000JK\u0005~\u0000\u0000K\u001c\u0001\u0000\u0000\u0000LN\u0007"+
		"\u0000\u0000\u0000ML\u0001\u0000\u0000\u0000NO\u0001\u0000\u0000\u0000"+
		"OM\u0001\u0000\u0000\u0000OP\u0001\u0000\u0000\u0000P\u001e\u0001\u0000"+
		"\u0000\u0000QS\u0007\u0001\u0000\u0000RQ\u0001\u0000\u0000\u0000ST\u0001"+
		"\u0000\u0000\u0000TR\u0001\u0000\u0000\u0000TU\u0001\u0000\u0000\u0000"+
		"U \u0001\u0000\u0000\u0000VX\u0007\u0001\u0000\u0000WV\u0001\u0000\u0000"+
		"\u0000XY\u0001\u0000\u0000\u0000YW\u0001\u0000\u0000\u0000YZ\u0001\u0000"+
		"\u0000\u0000Z[\u0001\u0000\u0000\u0000[_\u0005.\u0000\u0000\\^\u0007\u0001"+
		"\u0000\u0000]\\\u0001\u0000\u0000\u0000^a\u0001\u0000\u0000\u0000_]\u0001"+
		"\u0000\u0000\u0000_`\u0001\u0000\u0000\u0000`\"\u0001\u0000\u0000\u0000"+
		"a_\u0001\u0000\u0000\u0000bd\u0007\u0002\u0000\u0000cb\u0001\u0000\u0000"+
		"\u0000de\u0001\u0000\u0000\u0000ec\u0001\u0000\u0000\u0000ef\u0001\u0000"+
		"\u0000\u0000f$\u0001\u0000\u0000\u0000gi\u0007\u0003\u0000\u0000hg\u0001"+
		"\u0000\u0000\u0000ij\u0001\u0000\u0000\u0000jh\u0001\u0000\u0000\u0000"+
		"jk\u0001\u0000\u0000\u0000kl\u0001\u0000\u0000\u0000lm\u0006\u0012\u0000"+
		"\u0000m&\u0001\u0000\u0000\u0000\b\u0000MOTY_ej\u0001\u0006\u0000\u0000";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}