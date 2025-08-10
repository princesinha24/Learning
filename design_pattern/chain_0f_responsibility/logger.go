package main

import (
	"fmt"
)

// Enum-like log level
type LoggerType int

const (
	DEBUG LoggerType = iota
	INFO
	WARN
	ERROR
)

// Logger interface defines the methods
type Logger interface {
	SetNext(next Logger)
	Log(level LoggerType, message string)
}

// Base struct to share next-handler logic
type BaseLogger struct {
	next Logger
}

func (b *BaseLogger) SetNext(next Logger) {
	b.next = next
}

func (b *BaseLogger) CallNext(level LoggerType, message string) {
	if b.next != nil {
		b.next.Log(level, message)
	}
}

// DebugLogger
type DebugLogger struct {
	BaseLogger
}

func (d *DebugLogger) Log(level LoggerType, message string) {
	if level == DEBUG {
		fmt.Println("Debug:", message)
	}
	d.CallNext(level, message)
}

// InfoLogger
type InfoLogger struct {
	BaseLogger
}

func (i *InfoLogger) Log(level LoggerType, message string) {
	if level == INFO {
		fmt.Println("Info:", message)
	}
	i.CallNext(level, message)
}

// WarnLogger
type WarnLogger struct {
	BaseLogger
}

func (w *WarnLogger) Log(level LoggerType, message string) {
	if level == WARN {
		fmt.Println("Warn:", message)
	}
	w.CallNext(level, message)
}

// ErrorLogger
type ErrorLogger struct {
	BaseLogger
}

func (e *ErrorLogger) Log(level LoggerType, message string) {
	if level == ERROR {
		fmt.Println("Error:", message)
	}
	e.CallNext(level, message)
}

func main() {
	// Construct chain: Debug -> Info -> Warn -> Error
	debugLogger := &DebugLogger{}
	infoLogger := &InfoLogger{}
	warnLogger := &WarnLogger{}
	errorLogger := &ErrorLogger{}

	debugLogger.SetNext(infoLogger)
	infoLogger.SetNext(warnLogger)
	warnLogger.SetNext(errorLogger)

	// Start logging through the chain
	debugLogger.Log(DEBUG, "This is a debug message")
	debugLogger.Log(INFO, "This is an info message")
	debugLogger.Log(WARN, "This is a warning message")
	debugLogger.Log(ERROR, "This is an error message")
}
