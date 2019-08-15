 
#ifndef __SACHANNEL_H__
#define __SACHANNEL_H__

#include "types.h"
#include "MemPool.h"
#include "SubscriberUtils.h"

#define	SA_SUBS_MAX_CHANNELS		8		

#define	SA_SUBS_MAX_BUFFERS			8		

#define		INTERNAL_MUTE		false
#define		INTERNAL_UNMUTE		false
#define		USER_MUTE			true
#define		USER_UNMUTE			true

#define IsChanInitalized(x)	(x->channelOutput.instrument > 0)
#define IsChanEnabled(x)	(x->status & CHAN_ENABLED)
#define IsChanActive(x)		(x->status & CHAN_ACTIVE)


typedef struct SAudioOutput {
	Item				instrument;				/* instrument item */
	long				numChannels;			/* is instrument mono or stereo or ? */
	Item				leftEnv;				/* envelope instruments for channel amplitude ramping */
	Item				leftEnvTargetKnob;		/* knob to set target envelope value */
	Item				rightEnv;				
	Item				rightEnvTargetKnob;		/* knob to set target envelope value */
	long 				currentAmp;				
	long 				savedAmp;				/* previous amplitude to restore, used for muting */		
	Boolean				muted;					/* is channel in mute mode */
	Boolean				externalMute;			/* Should channel be unmuted by StartSAudioChannel()? */
	long 				currentPan;				
	} SAudioOutput, *SAudioOutputPtr;


struct SAudioBufferPtr;   /* forward ref */

typedef struct SAudioChannel {
	unsigned long			status;				/* state bits (see below) */
	long					numBuffers;			/* how many buffers to use for this channel */
	MemPoolPtr 				bufferPool;			/* pool of pre initalized attachments, cues, signals, and samples */
	Item					channelInstrument;	/* DSP instrument to play channel's data chunks */
	Boolean					instStarted;		/* flag to know if instrument is started */
	Boolean					instPaused;			/* flag to know if instrument is paused */
	ulong					pauseTime;			/* stream clock value when pause was initiated */
	Boolean					attachmentsRunning;	/* flag to know if attachments are running */
	ulong   				signalMask;			/* the ORd signals for all the current cues on this channel */
	SubsQueue				dataQueue;			/* waiting data chunks */
	long					inuseCount;			/* number of buffers currently in the in use queue */
	struct SAudioBuffer*	inuseQueueHead;		/* pointer to head of buffers queued to the audio folio */
	struct SAudioBuffer*	inuseQueueTail;		/* pointer to tail of buffers queued to the audio folio */
	SAudioOutput			channelOutput;		/* contains output instrument and control knobs */
	} SAudioChannel, *SAudioChannelPtr;
	

struct SAudioContext;
struct SAudioHeaderChunk;

#ifdef __cplusplus 
extern "C" {
#endif

long  	InitSAudioChannel( struct SAudioContext* ctx, struct SAudioHeaderChunk* headerPtr );
void	StartSAudioChannel(struct SAudioContext* ctx, long channelNumber, Boolean doFlush );
long	StopSAudioChannel( struct SAudioContext* ctx, long channelNumber, Boolean doFlush );
long	FlushSAudioChannel( struct SAudioContext* ctx, long channelNumber );
long	CloseSAudioChannel( struct SAudioContext* ctx, long channelNumber );

long	SetSAudioChannelAmplitude( struct SAudioContext* ctx, long channelNumber, long newAmp );
long	SetSAudioChannelPan( struct SAudioContext* ctx, long channelNumber, long newPan );
long	GetSAudioChannelAmplitude( struct SAudioContext* ctx, long channelNumber, long* Amp );
long	GetSAudioChannelPan( struct SAudioContext* ctx, long channelNumber, long* Pan );
long	MuteSAudioChannel( struct SAudioContext* ctx, long channelNumber, Boolean callerFlag );
long	UnMuteSAudioChannel( struct SAudioContext* ctx, long channelNumber, Boolean callerFlag );

void	BeginSAudioPlaybackIfAppropriate( struct SAudioContext* ctx, long channelNumber );

#ifdef __cplusplus
}
#endif

#endif	/* __SACHANNEL_H__ */
